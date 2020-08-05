#include "options.hpp"
#include "main_live084.hpp"
#include "enetserver.hpp"

int main(int argc, char** argv)
{
    uint32_t syncId = 1;
    r3dPoint2D lastPos = r3dPoint2D{ 26.0f, 280.0f };
    Options options = {argc, argv};

    auto server = ENetServer({ENET_HOST_ANY, 5119}, "GLzvuWtyCfHyGhF2");
    LOG_INFO("Server started!");

    server.onConnected = [&](int32_t from) {
        LOG_INFO("Peer connected: %d", from);
    };

    server.onDisconnected = [&](int32_t from) {
        LOG_INFO("Peer disconnected: %d", from);
    };

    server.onPacket[CHANNEL_MIDDLE_TIER_ROSTER] = [&](int32_t from, char const* data, size_t length) {
        (void)from;
        (void)data;
        (void)length;
        auto id = (egptype_e)data[0];
        if (id == egptype_e::EGP_RequestJoinTeam) {
            LOG_TRACE("Got EGP_RequestJoinTeam");
            EGP_TeamRosterUpdate_s res1 = {};
            res1.orderMembers[0] = from;
            res1.current_teamsize_order = 1;
            res1.current_teamsize_chaos = 0;
            res1.teamsize_order = 1;
            res1.teamsize_chaos = 0;
            server.send_simple(from, res1);

            EGP_RequestReskin_s res3 = {};
            res3.Id_Player = from;
            res3.skinID = options.SkinID;
            strcpy(&res3.buffer[0], options.ChampionName.c_str());
            res3.bufferLen = options.ChampionName.length() + 1;
            server.send_simple(from, res3);

            EGP_RequestRename_s res2 = {};
            res2.Id_Player = from;
            res2.skinID = options.SkinID;
            strcpy(&res2.buffer[0], options.PlayerName.c_str());
            res2.bufferLen = options.PlayerName.length();
            server.send_simple(from, res2);
            return;
        }
    };

    server.onPacket[CHANNEL_GENERIC_APP_TO_SERVER] = [&](int32_t from, char const* data, size_t length) {
        (void)from;
        (void)data;
        (void)length;
        auto id = (pkttype_e)(uint8_t)data[0];
        if (id == PKT_C2S_Reconnect) {
            LOG_DEBUG("Got PKT_C2S_Reconnect");
            PKT_S2C_Reconnect_s ans = {};
            ans.cid = from;
            server.send_simple(from, ans);
            return;
        }

        if (id == PKT_C2S_QueryStatusReq) {
            LOG_DEBUG("Got PKT_C2S_QueryStatusReq");
            PKT_S2C_QueryStatusAns_s ans = {};
            ans.ok = true;
            server.send_simple(from, ans);
            return;
        }

        if (id == PKT_SynchVersionC2S) {
            LOG_DEBUG("Got PKT_SynchVersionC2S");
            auto req = cast_packet<PKT_SynchVersionC2S_s>(data, length);
            PKT_SynchVersionS2C_s ans = {};
            ans.mIsVersionOk = true;
            ans.mMapToLoad = options.MapID;
            strcpy(&ans.mVersionString[0], &req->mVersionString[0]);
            ans.playerInfo[0].ID = from;
            ans.playerInfo[0].summonorLevel = 30;
            ans.playerInfo[0].summonorSpell1 = 0x06496EA8;
            ans.playerInfo[0].summonorSpell2 = 0x06496EA8;
            server.send_simple(from, ans);
            return;
        }

        if (id == PKT_C2S_Ping_Load_Info) {
            LOG_DEBUG("Got PKT_C2S_Ping_Load_Info");
            auto req = cast_packet<PKT_C2S_Ping_Load_Info_s>(data, length);
            PKT_S2C_Ping_Load_Info_s ans = {};
            ans.mConnectionInfo = req->mConnectionInfo;
            server.send_simple(from, ans);
            return;
        }

        if (id == PKT_C2S_CharSelected) {
            LOG_DEBUG("Got PKT_C2S_CharSelected");
            PKT_S2C_StartSpawn_s ans1 = {};
            ans1.numBotsChaos = 0;
            ans1.numBotsOrder = 0;
            server.send_simple(from, ans1);

            PKT_S2C_CreateHero_s ans3 = {};
            ans3.isBot = 0;
            ans3.teamIsOrder = 1;
            ans3.skinID = options.SkinID;
            strcpy(ans3.Skin, options.ChampionName.c_str());
            ans3.skillLevel = 1;
            ans3.playerUID = from;
            ans3.netObjID = 0x40000001;
            ans3.netNodeID = 0x40;
            strcpy(ans3.Name, options.PlayerName.c_str());
            server.send_simple(from, ans3);

            PKT_S2C_EndSpawn_s ans2 = {};
            server.send_simple(from, ans2);
            return;
        }

        if (id == PKT_C2S_ClientReady) {
            LOG_DEBUG("Got PKT_C2S_ClientReady");
            PKT_S2C_StartGame_s ans1 = {};
            server.send_simple(from, ans1);

            PKT_OnEnterVisiblityClient_s ans2 = {};
            std::stringstream buffer = {};
            ans2.fromID = 0x40000001;
            buffer <= ans2;
            for(int i = 0; i < 13; i++)
                buffer <= (uint8_t) 0;
            buffer <= (float) 1.0f;
            for(int i = 0; i < 13; i++)
                buffer <= (uint8_t) 0;
            buffer <= (uint8_t) 3;
            buffer <= (uint32_t) 1;
            buffer <= lastPos;
            buffer <= lastPos;
            server.send_variable(from, buffer, ans2.channel(), ans2.flag());
            return;
        }

        if (id == PKT_NPC_IssueOrderReq) {
            auto req = cast_packet<PKT_NPC_IssueOrderReq_s>(data, length);
            LOG_DEBUG("Got PKT_NPC_IssueOrderReq_s: order:%u, pos: %f %f %f, netid: 0x%08x",
              req->order, req->pos.x, req->pos.y, req->pos.z, req->targetNetID);
            if (req->order == 0x02) {
              r3dPoint2D end{ req->pos.x, req->pos.z };
              r3dPoint2D distance = end - lastPos;
              r3dPoint2D dir = distance / ::length(distance);
              LOG_DEBUG("Facing %f %f", dir.x, dir.y);

              PKT_S2C_FaceDirection_s ans2;
              ans2.fromID = 0x40000001;
              ans2.direction = { dir.x, 0, dir.y };
              server.send_simple(from, ans2);

              PKT_WaypointList_s ans;
              ans.fromID = 0x40000001;
              ans.syncID = syncId++;
              std::stringstream buffer;
              buffer <= ans;
              buffer <= end;
              server.send_variable(from, buffer, ans2.channel(), ans.flag());
              lastPos = end;
            }
            return;
        }
        LOG_WARNING("Unknown packet: 0x%02x = %u", data[0], data[0]);
    };

    for(;;) {
        server.service(10);
    }
    return 0;
}

