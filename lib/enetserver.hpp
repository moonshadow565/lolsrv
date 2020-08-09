#pragma once
#include <vector>
#include <map>
#include <array>
#include <cstring>
#include <memory>
#include <sstream>
#include <functional>
#include <enet/enet.h>
#include "log.hpp"
#include "blowfish.hpp"

struct ENetServer
{
    std::function<void(int32_t)> onConnected;
    std::function<void(int32_t)> onDisconnected;
    std::function<void(int32_t cid, char const* data, size_t size)> onPacket[8];

    ENetServer(ENetAddress const address, std::string_view const key) noexcept;
    void service(uint32_t timeout = 0) noexcept;
    template<typename PKT>
    inline void send_simple(int32_t cid, PKT const& pkt) {
        send_raw(cid, &pkt, sizeof(pkt), pkt.channel(), pkt.flag());
    }
    inline void send_variable(int32_t cid, std::stringstream const& pkt,
                              uint8_t channel, uint32_t flags = ENET_PACKET_FLAG_RELIABLE) {
        auto const data = pkt.str();
        send_raw(cid, data.data(), data.size(), channel, flags);
    }
private:
    BlowFish const blowfish;
    std::unique_ptr<ENetHost, void(*)(ENetHost*)> const host;
    std::map<int32_t, ENetPeer*> peers = {};

    bool route_auth(ENetPeer* peer, ENetPacket const* packet);
    void route_packet(int32_t cid, uint8_t channel, ENetPacket const* packet);
    void send_raw(int32_t cid, void const *pkt, size_t size, uint8_t channel, uint32_t flags);
};

template <typename T, class... StreamArgs>
inline std::basic_ostream<StreamArgs...> &
operator <= (std::basic_ostream<StreamArgs...> & out, T const & data)
{
    out.write(reinterpret_cast<char const *>(&data), sizeof(T));
    return out;
}

template <class... StreamArgs>
inline std::basic_ostream<StreamArgs...> &
operator <= (std::basic_ostream<StreamArgs...> & out, char const* const data)
{
    out.write(data, strlen(data) + 1);
    return out;
}

template<typename T>
T const* cast_packet(char const* data, size_t size) {
    if (size < sizeof(T)) {
        LOG_WARNING("%s: size(%X) < size(%X)", typeid(T).name(), (uint32_t)size, (uint32_t)sizeof(T));
    }
    return reinterpret_cast<T const*>(data);
}
