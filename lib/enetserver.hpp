#pragma once
#include <blowfish.hpp>
#include <enet/enet.h>
#include <functional>
#include <log.hpp>
#include <map>
#include <memory>

struct ENetServer {
    std::function<void()> onNone;
    std::function<void(int32_t)> onConnected;
    std::function<void(int32_t)> onDisconnected;
    std::function<void(uint8_t channel, int32_t cid, char const* data, size_t size)> onPacket;

    ENetServer(ENetAddress const address, std::string_view const key) noexcept;
    void service(uint32_t timeout = 0) noexcept;
    void send_raw(int32_t cid, void const* pkt, size_t size, uint8_t channel, uint32_t flags);

private:
    BlowFish const blowfish;
    std::unique_ptr<ENetHost, void (*)(ENetHost*)> const host;
    std::map<int32_t, ENetPeer*> peers = {};

    bool route_auth(ENetPeer* peer, ENetPacket const* packet);
    void route_packet(int32_t cid, uint8_t channel, ENetPacket const* packet);
};
