#pragma once
#include "options.hpp"
#include "proto_json.hpp"
#include "proto_pkt.hpp"

#include <functional>
#include <log.hpp>
#include <map>

struct ClientData {
    std::string command_buffer = {};
    // TODO:
    //    uint32_t teamID = 100;
    //    std::string playerName = "Test";
    //    std::string championName = "Annie";
    //    int32_t skinID = 0;
    uint32_t heroNetID = 0x4000'0001;
    r3dPoint2D lastPos = {};
    r3dPoint2D lastPingPos = {};
    r3dPoint3D lastOrderPos = {};
    uint32_t lastPingNetID = {};
    uint32_t lastSelectNetID = {};
    uint32_t lastOrderNetID = {};
};

struct Game {
    Options const& options;
    std::function<void(int32_t cid, PKT_S2C const&)> send_packet_impl = {};
    std::map<std::string, std::function<std::string(int32_t cid, std::string data)>> commands = {};
    std::map<int32_t, ClientData> clientData = {};
    uint32_t syncId = {};
    uint32_t nextNetID = 0x4000'0100u;

    Game(Options const& aoptions);

    void parse_command(int32_t cid, std::string_view data);

    void send_packet(int32_t cid, PKT_S2C pkt);

    void send_file(int32_t cid, std::string filename, IReplacer& replacer);

    void send_file(int32_t cid, std::string filename);

    void on_update();

    void on_connected(int32_t cid);

    void on_disconnected(int32_t cid);

    void on_packet(int32_t cid, EGP_RequestJoinTeam const& pkt);

    void on_packet(int32_t cid, EGP_Chat const& pkt);

    void on_packet(int32_t cid, PKT_BuyItemReq const& pkt);

    void on_packet(int32_t cid, PKT_C2S_CharSelected const& pkt);

    void on_packet(int32_t cid, PKT_C2S_ClientReady const& pkt);

    void on_packet(int32_t cid, PKT_C2S_MapPing const& pkt);

    void on_packet(int32_t cid, PKT_C2S_Ping_Load_Info const& pkt);

    void on_packet(int32_t cid, PKT_C2S_PlayEmote const& pkt);

    void on_packet(int32_t cid, PKT_C2S_QueryStatusReq const& pkt);

    void on_packet(int32_t cid, PKT_C2S_Reconnect const& pkt);

    void on_packet(int32_t cid, PKT_NPC_IssueOrderReq const& pkt);

    void on_packet(int32_t cid, PKT_NPC_UpgradeSpellReq const& pkt);

    void on_packet(int32_t cid, PKT_RemoveItemReq const& pkt);

    void on_packet(int32_t cid, PKT_SwapItemReq const& pkt);

    void on_packet(int32_t cid, PKT_SynchVersionC2S const& pkt);

    void on_packet(int32_t cid, PKT_World_LockCamera_Server const& pkt);

    void on_packet(int32_t cid, PKT_World_SendCamera_Server const& pkt);
};
