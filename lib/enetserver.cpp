#include "enetserver.hpp"

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <vector>

struct PKT_KeyCheck_s {
    uint8_t cmd = {};
    int32_t clientID = {};
    int64_t playerID = {};
    uint64_t checkId = {};
};

ENetServer::ENetServer(const ENetAddress address, const std::string_view key) noexcept
    : blowfish{key}, host{enet_host_create(&address, 32, 0, 0), &enet_host_destroy} {
    if (!host) {
        panic("enet_host_create(host: %08X, port: %u) == nullptr", address.host, address.port);
    }
}

void ENetServer::service(uint32_t timeout) noexcept {
    for (;;) {
        ENetEvent event = {};
        auto result = enet_host_service(host.get(), &event, timeout);
        if (result < 0) {
            panic("enet_host_service() < 0");
        }
        switch (event.type) {
        case ENET_EVENT_TYPE_NONE:
            if (onNone) {
                onNone();
            }
            break;
        case ENET_EVENT_TYPE_CONNECT:
            LOG_TRACE("ENET_EVENT_TYPE_CONNECT");
            event.peer->data = (void*)(intptr_t)(int32_t)-1;
            event.peer->mtu = 996;
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
            LOG_TRACE("ENET_EVENT_TYPE_DISCONNECT");
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
            LOG_TRACE("ENET_EVENT_TYPE_RECEIVE");
            if (int32_t cid = (int32_t)(intptr_t)(event.peer->data); cid != -1) {
                route_packet(cid, event.channelID, event.packet);
            } else {
                if (!route_auth(event.peer, event.packet)) {
                    LOG_DEBUG("Auth failiure!");
                    enet_peer_disconnect(event.peer, 0);
                }
            }
            enet_packet_destroy(event.packet);
            break;
        }
    }
}

void ENetServer::send_raw(int32_t cid, void const* pkt, size_t size, uint8_t channel, uint32_t flags) {
    auto const i = peers.find(cid);
    if (i == peers.end()) {
        return;
    }
    if (Logger::currentLevel >= LogLevel::LLOG_DEBUG) {
        uint8_t packetId = size ? (uint8_t)(*((char const*)pkt)) : 0;
        LOG_TRACE("Sending packet on %u to %u: 0x%02X, size : %u", channel, cid, packetId, size);
        puts(to_hex({(char const*)pkt, (char const*)pkt + size}).c_str());
    }
    auto packet = enet_packet_create(pkt, size, flags & ~ENET_PACKET_FLAG_NO_ALLOCATE);
    blowfish.encrypt((char*)packet->data, size);
    enet_peer_send(i->second, channel, packet);
}

bool ENetServer::route_auth(ENetPeer* peer, ENetPacket const* packet) {
    if (packet->dataLength < sizeof(PKT_KeyCheck_s)) {
        return false;
    }
    PKT_KeyCheck_s pkt = *(PKT_KeyCheck_s const*)(packet->data);
    LOG_DEBUG("Authing: %016llX with checkID of %016llX", pkt.playerID, pkt.checkId);
    std::array<char, 8> encrypted = {};
    std::memcpy(encrypted.data(), &pkt.checkId, 8);
    std::array<char, 8> decrypted = {};
    std::memcpy(decrypted.data(), &pkt.playerID, 8);
    blowfish.decrypt(encrypted.data(), 8);
    if (encrypted != decrypted) {
        return false;
    }
    pkt.cmd = 0;
    pkt.clientID = (int32_t)(pkt.playerID);
    peers[pkt.clientID] = peer;
    peer->data = (void*)(intptr_t)pkt.clientID;
    send_raw(pkt.clientID, &pkt, sizeof(pkt), 0, ENET_PACKET_FLAG_RELIABLE);
    if (onConnected) {
        onConnected(pkt.clientID);
    }
    return true;
}

void ENetServer::route_packet(int32_t cid, uint8_t channel, ENetPacket const* packet) {
    std::vector data = std::vector<char>((char const*)(packet->data), (char const*)(packet->data + packet->dataLength));
    blowfish.decrypt(data.data(), data.size());
    if (Logger::currentLevel >= LogLevel::LLOG_DEBUG) {
        uint8_t packetId = data.size() ? (uint8_t)(data[0]) : 0;
        LOG_TRACE("Reading packet on %u from %u: 0x%02X, size : %u", channel, cid, packetId, packet->dataLength);
        puts(to_hex(data).c_str());
    }
    if (onPacket) {
        onPacket(channel, cid, data.data(), data.size());
    }
}

static struct ENetInit {
    inline ENetInit() { enet_initialize(); }
    inline ~ENetInit() { enet_deinitialize(); }
} enet_init = {};
