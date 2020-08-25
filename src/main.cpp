#include <iterator>
#include <algorithm>
#include <log.hpp>
#include <enetserver.hpp>
#include "proto.hpp"
#include "options.hpp"
#include "game.hpp"

struct App {
private:
    Options options;
    ProtoBase const* protocol;
    Game game;
    ENetServer server;

    static inline constexpr std::string_view IGNORE_C2S_WARNINGS[] = {
        "PKT_Waypoint_Acc",
        "PKT_World_SendCamera_Server",
        "PKT_World_LockCamera_Server",
        "PKT_SendSelectedObjID",
    };
public:
    App(int argc, char** argv)
        : options(argc, argv),
          protocol(find_protocol(options.protocol)),
          game(options),
          server({ ENET_HOST_ANY, options.port }, options.key)
    {
        if (!protocol) {
            printf("Bad protocol: %s\n", options.protocol.c_str());
            printf("Aveliable protocols are: \n");
            for (auto const& p: proto_list()) {
                printf("\t%s\n", p->name().data());
            }
            exit(-1);
        }
    }

    void send_packet(int32_t cid, PKT_S2C const& pkt) {
        std::string name = {};
        auto channel = std::visit([&](auto const& pkt){
            using T = std::remove_cvref_t<decltype(pkt)>;
            LOG_INFO("sending: %s", std::string(type_name<T>()).c_str());
            if constexpr (std::is_base_of_v<DefaultPacket, T>) {
               return CHANNEL_GENERIC_APP_BROADCAST;
            } else {
               return CHANNEL_MIDDLE_TIER_ROSTER;
            }
        }, pkt);
        try {
            auto data = protocol->write_pkt(pkt);
            server.send_raw(cid, data.data(), data.size(), channel, ENET_PACKET_FLAG_RELIABLE);
        } catch(ProtoErrorNoID const& err) {
            LOG_ERROR("ProtoErrorNoID: %s", err.name.data());
        } catch(ProtoErrorIO const& err) {
            LOG_ERROR("ProtoErrorIO: %s @ %d", err.name.data(), (int32_t)err.position);
        } catch(ProtoErrorWriteNotImpl const& err) {
            LOG_ERROR("ProtoErrorWriteNotImpl: %s", err.name.data());
        } catch(std::exception const& err) {
            LOG_ERROR("std::exception: %s", err.what());
        }
    }

    void on_none() {
        game.on_update();
    }

    void on_connected(int32_t cid) {
        LOG_INFO("Peer: %d", cid);
        try {
            game.on_connected(cid);
        } catch(std::exception const& err) {
            LOG_ERROR("std::exception: %s", err.what());
        }
    }

    void on_disconnected(int32_t cid) {
        LOG_INFO("Peer: %d", cid);
        try {
            game.on_disconnected(cid);
        } catch(std::exception const& err) {
            LOG_ERROR("std::exception: %s", err.what());
        }
    }

    void on_packet(uint8_t channel, int32_t cid, char const* data, size_t size) {
        if (channel == CHANNEL_DEFAULT || channel == CHANNEL_MIDDLE_TIER_CHAT) {
            return;
        }
        try {
            auto pkt = protocol->read_pkt(Data_in{data, size}, (Channel)channel);
            std::visit([&](auto const& pkt) {
                using T = std::remove_cv_t<std::remove_reference_t<decltype(pkt)>>;
                LOG_INFO("reading: %s", std::string(type_name<T>()).c_str());
                game.on_packet(cid, pkt);
            }, pkt);
        } catch (ProtoErrorBadChannel const& err) {
            LOG_ERROR("ProtoErrorBadChannel: %u", err.channel);
        } catch(ProtoErrorIO const& err) {
            LOG_ERROR("ProtoErrorIO: %s @ %d", err.name.data(), (int32_t)err.position);
        } catch (ProtoErrorUnknownID const& err) {
            LOG_ERROR("ProtoErrorUnknownID: %u @ %u", err.id, err.channel);
        } catch (ProtoErrorReadNotImpl const& err) {
            if (std::find(std::begin(IGNORE_C2S_WARNINGS), std::end(IGNORE_C2S_WARNINGS), err.name) == std::end(IGNORE_C2S_WARNINGS)) {
                LOG_WARNING("ProtoErrorReadNotImpl: %s", err.name.data());
            }
        } catch(std::exception const& err) {
            LOG_ERROR("std::exception: %s", err.what());
        }
    }

    void run() {
        LOG_INFO("started!");
        game.send_packet = std::bind_front(&App::send_packet, this);
        server.onNone = std::bind_front(&App::on_none, this);
        server.onConnected = std::bind_front(&App::on_connected, this);
        server.onDisconnected = std::bind_front(&App::on_disconnected, this);
        server.onPacket = std::bind_front(&App::on_packet, this);
        server.service();
    }
};

int main(int argc, char** argv) {
    App app { argc, argv };
    app.run();
}
