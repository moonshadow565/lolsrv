#include "game.hpp"

#include "game_replacer.hpp"

#include <fstream>
#include <json.hpp>
#include <r3d_ops.hpp>
#include <regex>

static auto R_NAME_OPT = std::regex(R"(\s*([^\s]+)(.*))");

Game::Game(const Options& aoptions) : options(aoptions) {
    commands.insert_or_assign("!", [this](auto cid, auto data) -> std::string {
        std::smatch results;
        if (!std::regex_match(data, results, R_NAME_OPT)) {
            throw std::runtime_error("Invalid syntax: !<path>");
        }
        GameReplacerWithArgs replacer(this, cid, std::string(results[2]));
        send_file(cid, results[1], replacer);
        return "Ok!";
    });
}

void Game::parse_command(int32_t cid, std::string_view data) {
    for (auto& [command, execute] : commands) {
        if (data.starts_with(command)) {
            auto body = std::string(data.substr(command.size()));
            try {
                auto result = execute(cid, body);
                send_packet(cid, EGP_Chat{.message = result});
            } catch (std::exception const& err) {
                LOG_ERROR("Failed to run command(%s): %s", command.c_str(), err.what());
                send_packet(cid, EGP_Chat{.clientID = cid, .message = std::string("Error: ") + err.what()});
            }
            break;
        }
    }
}

void Game::send_packet(int32_t cid, PKT_S2C pkt) {
    send_packet_impl(cid, pkt);
    std::visit(
        [this]<typename T>(T& value) {
            if constexpr (std::is_base_of_v<WithSyncID, T>) {
                if (value.syncID < syncId) {
                    value.syncID = ++syncId;
                }
            }
        },
        pkt);
}

void Game::send_file(int32_t cid, std::string filename, IReplacer& replacer) {
    std::u8string buffer = {};
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            file.open("pkt/quick/" + filename + ".js", std::ios::binary);
        }
        if (!file) {
            throw std::ifstream::failure("File not found: " + filename);
        }
        file.seekg(0, std::ios::end);
        auto const end = file.tellg();
        file.seekg(0, std::ios::beg);
        auto const beg = file.tellg();
        auto const size = (std::streamsize)(end - beg);
        buffer.resize((size_t)size);
        file.read((char*)buffer.data(), size);
    }
    auto pkts = pkts_from_json(buffer, replacer);
    for (auto const& pkt : pkts) {
        send_packet(cid, pkt);
    }
}

void Game::send_file(int32_t cid, std::string filename) {
    try {
        GameReplacer replacer(this, cid);
        return send_file(cid, filename, replacer);
    } catch (std::ifstream::failure const&) {
        // ignore
    } catch (std::exception const& err) {
        LOG_ERROR("Failed to deserialize: %s", err.what());
    }
}

void Game::on_update() {}

void Game::on_connected(int32_t cid) {
    (void)cid;
    clientData[cid].command_buffer.clear();
    syncId = 1;
    clientData[cid].lastPos = r3dPoint2D{26.0f, 280.0f};
}

void Game::on_disconnected(int32_t cid) {
    (void)cid;
    clientData[cid].command_buffer.clear();
}

void Game::on_packet(int32_t cid, EGP_RequestJoinTeam const& pkt) {
    (void)cid;
    (void)pkt;
    if (!options.black_screen) {
        send_packet(cid,
                    EGP_TeamRosterUpdate{
                        .teamsize_order = 1,
                        .teamsize_chaos = 0,
                        .orderMembers = {cid},
                        .chaosMembers = {},
                        .current_teamsize_order = 1,
                        .current_teamsize_chaos = 0,
                    });
        send_packet(cid,
                    EGP_RequestReskin{
                        .Id_Player = cid,
                        .skinID = options.SkinID,
                        .buffer = options.ChampionName,
                    });
        send_packet(cid,
                    EGP_RequestRename{
                        .Id_Player = cid,
                        .skinID = options.SkinID,
                        .buffer = options.PlayerName,
                    });
    }
}

void Game::on_packet(int32_t cid, EGP_Chat const& pkt) {
    (void)cid;
    (void)pkt;
    LOG_DEBUG("from %d @ %u: `%s`\n", cid, pkt.chatType, pkt.message.c_str());
    if (pkt.message.ends_with("\\")) {
        auto& buffer = clientData[cid].command_buffer;
        buffer.append(pkt.message.substr(0, pkt.message.size() - 1));
        if (pkt.message.size() == 1) {
            parse_command(cid, buffer);
            buffer.clear();
        }
    } else {
        parse_command(cid, pkt.message);
    }
}

void Game::on_packet(int32_t cid, PKT_BuyItemReq const& pkt) {
    (void)cid;
    (void)pkt;
}

void Game::on_packet(int32_t cid, PKT_C2S_CharSelected const& pkt) {
    (void)cid;
    (void)pkt;
    send_packet(cid,
                PKT_S2C_StartSpawn{
                    .numBotsOrder = 0,
                    .numBotsChaos = 0,
                });
    send_packet(cid,
                PKT_S2C_CreateHero{
                    .netObjID = clientData[cid].heroNetID,
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
    send_file(cid, "pkt/on_spawn/all.js");
    send_file(cid, "pkt/on_spawn/" + options.protocol + ".js");
    send_packet(cid, PKT_S2C_EndSpawn{});
}

void Game::on_packet(int32_t cid, PKT_C2S_ClientReady const& pkt) {
    (void)cid;
    (void)pkt;
    send_packet(cid, PKT_S2C_StartGame{});
    send_packet(cid,
                PKT_OnEnterVisiblityClient{
                    .fromID = clientData[cid].heroNetID,
                    .position = clientData[cid].lastPos,
                });
    send_file(cid, "pkt/on_start/all.js");
    send_file(cid, "pkt/on_start/" + options.protocol + ".js");
}

void Game::on_packet(int32_t cid, PKT_C2S_MapPing const& pkt) {
    (void)cid;
    (void)pkt;
    clientData[cid].lastPingPos = {pkt.pos.x, pkt.pos.z};
    clientData[cid].lastPingNetID = pkt.target;
    LOG_DEBUG("Ping 0x%08X @[%f, %f, %f]", pkt.pos.x, pkt.pos.y, pkt.pos.z, pkt.target);
    send_packet(cid,
                PKT_S2C_MapPing{
                    .fromID = clientData[cid].heroNetID,
                    .pos = pkt.pos,
                    .target = pkt.target,
                    .src = clientData[cid].heroNetID,
                    .pingCategory = pkt.pingCategory,
                    .bPlayAudio = true,
                    .bShowChat = false,
                    .bPingThrottled = false,
                });
}

void Game::on_packet(int32_t cid, PKT_C2S_Ping_Load_Info const& pkt) {
    (void)cid;
    (void)pkt;
    if (!options.black_screen) {
        send_packet(cid,
                    PKT_S2C_Ping_Load_Info{
                        .mConnectionInfo = pkt.mConnectionInfo,
                    });
    }
}

void Game::on_packet(int32_t cid, PKT_C2S_PlayEmote const& pkt) {
    (void)cid;
    (void)pkt;
    LOG_DEBUG("Playing emote: %u", pkt.mEmoteId);
    send_packet(cid,
                PKT_S2C_PlayEmote{
                    .fromID = clientData[cid].heroNetID,
                    .mEmoteId = pkt.mEmoteId,
                });
}

void Game::on_packet(int32_t cid, PKT_C2S_QueryStatusReq const& pkt) {
    (void)cid;
    (void)pkt;
    send_packet(cid,
                PKT_S2C_QueryStatusAns{
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
    clientData[cid].lastOrderPos = pkt.pos;
    if (pkt.order == 0x02) {
        r3dPoint2D end{pkt.pos.x, pkt.pos.z};
        r3dPoint2D distance = end - clientData[cid].lastPos;
        r3dPoint2D dir = distance / ::length(distance);
        send_packet(cid,
                    PKT_S2C_FaceDirection{
                        .fromID = clientData[cid].heroNetID,
                        .direction = {dir.x, 0.0f, dir.y},
                    });
        send_packet(cid,
                    PKT_WaypointList{.fromID = clientData[cid].heroNetID,
                                     .list = {
                                         end,
                                     }});
        clientData[cid].lastPos = end;
    }
}

void Game::on_packet(int32_t cid, PKT_NPC_UpgradeSpellReq const& pkt) {
    (void)cid;
    (void)pkt;
}

void Game::on_packet(int32_t cid, PKT_RemoveItemReq const& pkt) {
    (void)cid;
    (void)pkt;
}

void Game::on_packet(int32_t cid, PKT_SwapItemReq const& pkt) {
    (void)cid;
    (void)pkt;
}

void Game::on_packet(int32_t cid, PKT_SynchVersionC2S const& pkt) {
    (void)cid;
    (void)pkt;
    send_packet(cid,
                PKT_SynchVersionS2C{
                    .mIsVersionOk = true,
                    .mMapToLoad = options.MapID,
                    .playerInfo = {PlayerLiteInfo{
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
                    }},
                    .mVersionString = pkt.mVersionString,
                    .mMapMode = {},
                });
}

void Game::on_packet(int32_t cid, PKT_World_LockCamera_Server const& pkt) {
    (void)cid;
    (void)pkt;
}

void Game::on_packet(int32_t cid, PKT_World_SendCamera_Server const& pkt) {
    (void)cid;
    (void)pkt;
    //    send_packet(cid, PKT_World_SendCamera_Server_Acknologment {
    //                    .syncID = (int8_t)(pkt.syncID + 1)
    //                });
}
