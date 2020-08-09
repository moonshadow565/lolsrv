#include <iostream>
#include <cctype>
#include "enetserver.hpp"

struct PKT_KeyCheck_s
{
    uint8_t cmd = {};
    int32_t clientID = {};
    int64_t playerID = {};
    uint64_t checkId = {};

    static inline constexpr uint32_t flag() noexcept {
        return ENET_PACKET_FLAG_RELIABLE;
    }
    static inline constexpr uint8_t channel() noexcept {
        return 0;
    }
};

ENetServer::ENetServer(const ENetAddress address, const std::string_view key) noexcept
    : blowfish{key}, host{enet_host_create(&address, 32, 0, 0), &enet_host_destroy}
{
    if (!host) {
        panic("host: %08X, port: %u", address.host, address.port);
    }
}

void ENetServer::service(uint32_t timeout) noexcept {
    for (;;) {
        ENetEvent event = {};
        auto result = enet_host_service(host.get(), &event, timeout);
        if (result < 0) {
            panic("result < 0");
        }
        switch(event.type)
        {
            case ENET_EVENT_TYPE_NONE:
                break;
            case ENET_EVENT_TYPE_CONNECT:
                LOG_TRACE("Got ENET_EVENT_TYPE_CONNECT");
                event.peer->data = (void*)(intptr_t)(int32_t)-1;
                event.peer->mtu = 996;
            break;
            case ENET_EVENT_TYPE_DISCONNECT:
                LOG_TRACE("Got ENET_EVENT_TYPE_DISCONNECT");
                if (int32_t cid = (int32_t)(intptr_t)(event.peer->data); cid != -1) {
                    if (auto i = peers.find(cid); i != peers.end()) {
                        peers.erase(i);
                    }
                    if (onDisconnected) {
                        onDisconnected(cid);
                    }
                }
            break;
            case ENET_EVENT_TYPE_RECEIVE:
                LOG_TRACE("Got ENET_EVENT_TYPE_RECEIVE");
                if (int32_t cid = (int32_t)(intptr_t)(event.peer->data); cid != -1) {
                    route_packet(cid, event.channelID, event.packet);
                } else {
                    if (!route_auth(event.peer, event.packet)) {
                        LOG_DEBUG("failed to auth!");
                        enet_peer_disconnect(event.peer, 0);
                    }
                }
                enet_packet_destroy(event.packet);
            break;
        }
    }
}

void ENetServer::send_raw(int32_t cid, void const *pkt, size_t size, uint8_t channel, uint32_t flags) {
    auto const i = peers.find(cid);
    if (i == peers.end()) {
        return;
    }
    auto const peer = i->second;
    auto const extra = 8 - (size % 8);
    auto packet = enet_packet_create(pkt, size + extra, flags & ~ENET_PACKET_FLAG_NO_ALLOCATE);
    memcpy(packet->data, pkt, size);
    if (extra)
        memset(packet->data + size, 0, extra);
    blowfish.encrypt((char*)packet->data, size + extra);
    enet_peer_send(peer, channel, packet);
}

bool ENetServer::route_auth(ENetPeer *peer, ENetPacket const* packet) {
    if(packet->dataLength < sizeof(PKT_KeyCheck_s)) {
        return false;
    }
    PKT_KeyCheck_s pkt = *(PKT_KeyCheck_s const*)(packet->data);
    LOG_DEBUG("Authing: %016llX with checkID of %016llX", pkt.playerID, pkt.checkId);
    std::array<char, 8> encrypted = {};
    memcpy(encrypted.data(), &pkt.checkId, 8);
    std::array<char, 8> decrypted = {};
    memcpy(decrypted.data(), &pkt.playerID, 8);
    blowfish.decrypt(encrypted.data(), 8);
    if (encrypted != decrypted) {
        return false;
    }
    pkt.cmd = 0;
    pkt.clientID = (int32_t)(pkt.playerID);
    peers[pkt.clientID] = peer;
    peer->data = (void*)(intptr_t)pkt.clientID;
    send_simple(pkt.clientID, pkt);
    if (onConnected) {
        onConnected(pkt.clientID);
    }
    return true;
}

void ENetServer::route_packet(int32_t cid, uint8_t channel, ENetPacket const* packet) {
    if(channel >= 8) {
        LOG_ERROR("Uknown channel: %u from %d", channel, cid);
        return;
    }
    std::vector data = std::vector<char>((char const*)(packet->data), (char const*)(packet->data + packet->dataLength));
    blowfish.decrypt(data.data(), data.size());
    uint8_t packetId = (uint8_t)(data[0]);
    LOG_DEBUG("Got packet on %u from %u: 0x%02x = %u, size : %u", channel, cid, packetId, packetId, packet->dataLength);
    if (Logger::currentLevel >= LogLevel::LLOG_TRACE) {
      for (size_t i = 0; i < data.size(); i += 8) {
        for (size_t c = i; c < data.size() && c < (i + 8); c++) {
          uint8_t z = data.data()[c];
          printf("%02X ", z);
        }
        for (size_t c = i; c < data.size() && c < (i + 8); c++) {
          uint8_t z = data.data()[c];
          if (z < 0x7f && z > 0x1f)
            printf("  %c", z);
          else
            printf(" ..");
        }
        printf("\n");
      }
    }
    auto& handler = onPacket[channel];
    if (handler) {
        handler(cid, data.data(), data.size());
    }
}

struct ENetInit {
    ENetInit() {
        enet_initialize();
    }
    ~ENetInit() {
        enet_deinitialize();
    }
};

static ENetInit enet_init = {};
