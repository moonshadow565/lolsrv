#pragma once
#include "proto/pkt.hpp"
#include "options.hpp"
#include <log.hpp>
#include <functional>

struct Game {
    std::function<void(int32_t cid, PKT_S2C const&)> send_packet;
    Options const& options;
    uint32_t syncId = {};
    r3dPoint2D lastPos = {};

    Game(Options const& aoptions);

    void on_update();

    void on_connected(int32_t cid);

    void on_disconnected(int32_t cid);

    void on_packet(int32_t cid, EGP_RequestJoinTeam const& pkt);

    void on_packet(int32_t cid, PKT_C2S_CharSelected const& pkt);

    void on_packet(int32_t cid, PKT_C2S_ClientReady const& pkt);

    void on_packet(int32_t cid, PKT_C2S_Ping_Load_Info const& pkt);

    void on_packet(int32_t cid, PKT_C2S_QueryStatusReq const& pkt);

    void on_packet(int32_t cid, PKT_C2S_Reconnect const& pkt);

    void on_packet(int32_t cid, PKT_NPC_IssueOrderReq const& pkt);

    void on_packet(int32_t cid, PKT_SynchVersionC2S const& pkt);
};
