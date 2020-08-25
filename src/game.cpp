#include "game.hpp"

Game::Game(const Options& aoptions)
    : options(aoptions) {
}

void Game::on_update() {

}

void Game::on_connected(int32_t cid) {
    (void)cid;
    syncId = 1;
    lastPos = r3dPoint2D{ 26.0f, 280.0f };
}

void Game::on_disconnected(int32_t cid) {
    (void)cid;
}

void Game::on_packet(int32_t cid, EGP_RequestJoinTeam const& pkt) {
    (void)cid;
    (void)pkt;
    if (!options.black_screen) {
        send_packet(cid, EGP_TeamRosterUpdate {
                        .teamsize_order = 1,
                        .teamsize_chaos = 0,
                        .orderMembers = { cid },
                        .chaosMembers = {},
                        .current_teamsize_order = 1,
                        .current_teamsize_chaos = 0,
                    });
        send_packet(cid, EGP_RequestReskin {
                        .Id_Player = cid,
                        .skinID = options.SkinID,
                        .buffer = options.ChampionName,
                    });
        send_packet(cid, EGP_RequestRename {
                        .Id_Player = cid,
                        .skinID = options.SkinID,
                        .buffer = options.PlayerName,
                    });
    }
}

void Game::on_packet(int32_t cid, PKT_C2S_CharSelected const& pkt) {
    (void)cid;
    (void)pkt;
    send_packet(cid, PKT_S2C_StartSpawn {
                    .numBotsOrder = 0,
                    .numBotsChaos = 0,
                });
    send_packet(cid, PKT_S2C_CreateHero {
                    .netObjID = 0x40000001,
                    .playerUID = cid,
                    .netNodeID = 0x40,
                    .skillLevel = 1,
                    .teamIsOrder = true,
                    .isBot = false,
                    .botRank = 0,
                    .spawnPosIndex = 0,
                    .skinID = options.SkinID,
                    .Name = options.PlayerName,
                    .Skin = options.ChampionName,
                });
    send_packet(cid, PKT_S2C_EndSpawn {
                });
}

void Game::on_packet(int32_t cid, PKT_C2S_ClientReady const& pkt) {
    (void)cid;
    (void)pkt;
    send_packet(cid, PKT_S2C_StartGame {
                });
    send_packet(cid, PKT_OnEnterVisiblityClient {
                    .fromID = 0x40000001,
                    .position = lastPos,
                });
}

void Game::on_packet(int32_t cid, PKT_C2S_Ping_Load_Info const& pkt) {
    (void)cid;
    (void)pkt;
    if (!options.black_screen) {
        send_packet(cid, PKT_S2C_Ping_Load_Info {
                        .mConnectionInfo = pkt.mConnectionInfo,
                    });
    }
}

void Game::on_packet(int32_t cid, PKT_C2S_QueryStatusReq const& pkt) {
    (void)cid;
    (void)pkt;
    send_packet(cid, PKT_S2C_QueryStatusAns {
                    .ok = true,
                });
}

void Game::on_packet(int32_t cid, PKT_C2S_Reconnect const& pkt) {
    (void)cid;
    (void)pkt;
    //        send_packet(cid, PKT_S2C_Reconnect {
    //                       .cid = cid,
    //                    });
}

void Game::on_packet(int32_t cid, PKT_NPC_IssueOrderReq const& pkt) {
    (void)cid;
    (void)pkt;
    if (pkt.order == 0x02) {
        r3dPoint2D end{ pkt.pos.x, pkt.pos.z };
        r3dPoint2D distance = end - lastPos;
        r3dPoint2D dir = distance / ::length(distance);
        send_packet(cid, PKT_S2C_FaceDirection {
                        .fromID = 0x40000001,
                        .direction = { dir.x, 0.0f, dir.y },
                    });
        send_packet(cid, PKT_WaypointList {
                        .fromID = 0x40000001,
                        .list = {
                            end,
                        }
                    });
        lastPos = end;
    }
}

void Game::on_packet(int32_t cid, PKT_SynchVersionC2S const& pkt) {
    (void)cid;
    (void)pkt;
    send_packet(cid, PKT_SynchVersionS2C {
                    .mIsVersionOk = true,
                    .mMapToLoad = options.MapID,
                    .playerInfo = {
                        PlayerLiteInfo {
                            .ID = cid,
                            .summonorLevel = 30,
                            .summonorSpell1 = 0x06496EA8,
                            .summonorSpell2 = 0x06496EA8,
                            .isBot = false,
                            .teamId = 100,
                            .botName = {},
                            .skinName = {},
                            .botDifficulty = {},
                            .profileIconId = {},
                        }
                    },
                    .mVersionString = pkt.mVersionString,
                    .mMapMode = {},
                });
}
