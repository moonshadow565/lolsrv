#include "proto_pkt.hpp"
#include "json.hpp"
#include "log.hpp"

using namespace std::string_literals;
using namespace std::string_view_literals;
using Null = Json::Null;
using Boolean = Json::Boolean;
using Number = Json::Number;
using String = Json::String;
using StringView = Json::StringView;
using Array = Json::Array;
using Object = Json::Object;

inline void operator>>(Json const& json, std::string& value) {
    auto const& str = json.get<Json::String>();
    value = std::string((char const*)str.data(), str.size());
}

inline void operator>>(Json const& json, r3dPoint2D& value) {
    if (json.is<Object>()) {
        auto const& object = json.get<Object>();
        value = {
            object.at(u8"x").into<float>(),
            object.at(u8"y").into<float>(),
        };
    } else {
        auto const& array = json.get<Array>();
        value = {
            array.at(0).into<float>(),
            array.at(1).into<float>(),
        };
    }
}

inline void operator>>(Json const& json, r3dPoint3D& value) {
    if (json.is<Object>()) {
        auto const& object = json.get<Object>();
        value = {
            object.at(u8"x").into<float>(),
            object.at(u8"y").into<float>(),
            object.at(u8"z").into<float>(),
        };
    } else {
        auto const& array = json.get<Array>();
        value = {
            array.at(0).into<float>(),
            array.at(1).into<float>(),
            array.at(2).into<float>(),
        };
    }
}

#define FIELD(name, ...) \
    do { if (json.contains(u8""#name)) value.name = json.at(u8""#name).into<__VA_ARGS__>(); } while(false)

inline void operator >> (Json const& json, CommonBasicAttack& value) {
    FIELD(targetNetId, uint32_t);
    FIELD(extraTime, float);
    FIELD(missileNextID, uint32_t);
    FIELD(attackSlot, uint8_t);
}

inline void operator >> (Json const& json, ConnectionInfo& value) {
    FIELD(mClientID, int32_t);
    FIELD(mPlayerID, int64_t);
    FIELD(mPercentage, float);
    FIELD(mETA, float);
    FIELD(mCount, int16_t);
    FIELD(mPing, uint16_t);
    FIELD(mPad, uint8_t);
    FIELD(mReady, uint8_t);
    FIELD(mState, std::string);
}

inline void operator >> (Json const& json, PlayerLiteInfo& value) {
    FIELD(ID, int64_t);
    FIELD(summonorLevel, uint16_t);
    FIELD(summonorSpell1, uint32_t);
    FIELD(summonorSpell2, uint32_t);
    FIELD(isBot, bool);
    FIELD(teamId, uint32_t);
    FIELD(botName, std::string);
    FIELD(skinName, std::string);
    FIELD(botDifficulty, uint32_t);
    FIELD(profileIconId, uint32_t);
}

inline void operator >> (Json const& json, ItemData& value) {
    FIELD(itemID, uint32_t);
    FIELD(slot, uint8_t);
    FIELD(itemsInSlot, uint8_t);
    FIELD(spellCharges, uint8_t);
}

inline void operator >> (Json const& json, EGP_RequestRename& value) {
    FIELD(Id_Player, int64_t);
    FIELD(skinID, int32_t);
    FIELD(buffer, std::string);
}

inline void operator >> (Json const& json, EGP_RequestReskin& value) {
    FIELD(Id_Player, int64_t);
    FIELD(skinID, int32_t);
    FIELD(buffer, std::string);
}

inline void operator >> (Json const& json, EGP_TeamRosterUpdate& value) {
    FIELD(teamsize_order, uint32_t);
    FIELD(teamsize_chaos, uint32_t);
    FIELD(orderMembers, std::array<int64_t, 24>);
    FIELD(chaosMembers, std::array<int64_t, 24>);
    FIELD(current_teamsize_order, uint32_t);
    FIELD(current_teamsize_chaos, uint32_t);
}

inline void operator >> (Json const& json, EGP_Chat& value) {
    FIELD(clientID, int32_t);
    FIELD(chatType, uint32_t);
    FIELD(message, std::string);
}

inline void operator >> (Json const& json, PKT_Basic_Attack& value) {
    FIELD(fromID, uint32_t);
    FIELD(data, CommonBasicAttack);
}

inline void operator >> (Json const& json, PKT_Basic_Attack_Pos& value) {
    FIELD(fromID, uint32_t);
    FIELD(data, CommonBasicAttack);
    FIELD(pos, r3dPoint2D);
}

inline void operator >> (Json const& json, PKT_BuyItemAns& value) {
    FIELD(fromID, uint32_t);
    FIELD(slot, uint8_t);
    FIELD(itemID, uint32_t);
    FIELD(itemsInSlot, uint8_t);
    FIELD(useOnBought, bool);
}

inline void operator >> (Json const& json, PKT_NPC_Die& value) {
    FIELD(fromID, uint32_t);
    FIELD(killerNetID, uint32_t);
    FIELD(damageType, uint8_t);
    FIELD(mSpellSourceType, uint8_t);
    FIELD(DeathDuration, float);
    FIELD(becomeZombie, bool);
}

inline void operator >> (Json const& json, PKT_NPC_LevelUp& value) {
    FIELD(fromID, uint32_t);
    FIELD(mLevel, uint8_t);
    FIELD(mPoints, uint8_t);
}

inline void operator >> (Json const& json, PKT_NPC_UpgradeSpellAns& value) {
    FIELD(fromID, uint32_t);
    FIELD(slot, uint8_t);
    FIELD(spellLevel, uint8_t);
    FIELD(spellTrainingPoints, uint8_t);
}

inline void operator >> (Json const& json, PKT_OnEnterVisiblityClient& value) {
    FIELD(fromID, uint32_t);
    FIELD(items, std::vector<ItemData>);
    FIELD(lookat, std::optional<r3dPoint3D>);
    FIELD(position, std::optional<r3dPoint2D>);
    FIELD(syncID, uint32_t);
}

inline void operator >> (Json const& json, PKT_RemoveItemAns& value) {
    FIELD(fromID, uint32_t);
    FIELD(slot, uint8_t);
    FIELD(itemsInSlot, uint8_t);
}

inline void operator >> (Json const& json, PKT_S2C_ChangeCharacterData& value) {
    FIELD(fromID, uint32_t);
    FIELD(id, uint32_t);
    FIELD(useSpells, bool);
    FIELD(skinName, std::string);
}

inline void operator >> (Json const& json, PKT_S2C_CreateHero& value) {
    FIELD(fromID, uint32_t);
    FIELD(netObjID, uint32_t);
    FIELD(playerUID, int32_t);
    FIELD(netNodeID, uint8_t);
    FIELD(skillLevel, uint8_t);
    FIELD(teamIsOrder, bool);
    FIELD(isBot, bool);
    FIELD(botRank, uint8_t);
    FIELD(spawnPosIndex, uint8_t);
    FIELD(skinID, int32_t);
    FIELD(Name, std::string);
    FIELD(Skin, std::string);
}

inline void operator >> (Json const& json, PKT_S2C_CreateTurret& value) {
    FIELD(fromID, uint32_t);
    FIELD(netObjID, uint32_t);
    FIELD(netNodeID, uint8_t);
    FIELD(Name, std::string);
}

inline void operator >> (Json const& json, PKT_S2C_FaceDirection& value) {
    FIELD(fromID, uint32_t);
    FIELD(direction, r3dPoint3D);
}

inline void operator >> (Json const& json, PKT_S2C_EndSpawn& value) {
    FIELD(fromID, uint32_t);
}

inline void operator >> (Json const& json, PKT_S2C_MapPing& value) {
    FIELD(fromID, uint32_t);
    FIELD(pos, r3dPoint3D);
    FIELD(target, uint32_t);
    FIELD(src, uint32_t);
    FIELD(pingCategory, uint8_t);
    FIELD(bPlayAudio, bool);
    FIELD(bShowChat, bool);
    FIELD(bPingThrottled, bool);
}

inline void operator >> (Json const& json, PKT_S2C_Ping_Load_Info& value) {
    FIELD(fromID, uint32_t);
    FIELD(mConnectionInfo, ConnectionInfo);
}

inline void operator >> (Json const& json, PKT_S2C_PlayAnimation& value) {
    FIELD(fromID, uint32_t);
    FIELD(flags, uint32_t);
    FIELD(scaleTime, float);
    FIELD(animationName, std::string);
}

inline void operator >> (Json const& json, PKT_S2C_PlayEmote& value) {
    FIELD(fromID, uint32_t);
    FIELD(mEmoteId, uint32_t);
}

inline void operator >> (Json const& json, PKT_S2C_QueryStatusAns& value) {
    FIELD(fromID, uint32_t);
    FIELD(ok, bool);
}

inline void operator >> (Json const& json, PKT_S2C_Reconnect& value) {
    FIELD(fromID, uint32_t);
    FIELD(cid, int32_t);
}

inline void operator >> (Json const& json, PKT_S2C_StartGame& value) {
    FIELD(fromID, uint32_t);
    FIELD(tournamentEnabled, uint8_t);
}

inline void operator >> (Json const& json, PKT_S2C_StartSpawn& value) {
    FIELD(fromID, uint32_t);
    FIELD(numBotsOrder, uint8_t);
    FIELD(numBotsChaos, uint8_t);
}

inline void operator >> (Json const& json, PKT_S2C_ToggleFoW& value) {
    FIELD(fromID, uint32_t);
}

inline void operator >> (Json const& json, PKT_SynchVersionS2C& value) {
    FIELD(fromID, uint32_t);
    FIELD(mIsVersionOk, bool);
    FIELD(mMapToLoad, int);
    FIELD(playerInfo, std::array<PlayerLiteInfo, 12>);
    FIELD(mVersionString, std::string);
    FIELD(mMapMode, std::string);
}

inline void operator >> (Json const& json, PKT_SwapItemAns& value) {
    FIELD(fromID, uint32_t);
    FIELD(source, uint8_t);
    FIELD(dest, uint8_t);
}

inline void operator >> (Json const& json, PKT_WaypointList& value) {
    FIELD(fromID, uint32_t);
    FIELD(syncID, uint32_t);
    FIELD(list, std::vector<r3dPoint2D>);
}

inline void operator >> (Json const& json, PKT_World_SendCamera_Server_Acknologment& value) {
    FIELD(fromID, uint32_t);
    FIELD(syncID, int8_t);
}

template<typename T>
inline bool deserialize_pkt_impl(Json const& json, std::string const& name, PKT_S2C& value) {
    if (name != type_name<T>()) {
        return false;
    }
    LOG_TRACE("Deserailizing: %s\n", name.c_str());
    value = json.into<T>();
    return true;
}

template<typename...T>
inline void deserialize_pkt_impl(Json const& json, std::string const& name, std::variant<T...>& value) {
    auto found = (deserialize_pkt_impl<T>(json, name, value) || ...);
    if (!found) {
        throw std::runtime_error("Pkt not found: " + name);
    }
}

inline void operator >> (Json const& json, PKT_S2C& value) {
    auto name = json.at(u8"pkt").into<std::string>();
    deserialize_pkt_impl(json, name, value);
}

inline void replace_json(Json& json, Object const& repl) {
    if (repl.empty()) {
        return;
    }
    if (auto str = json.get_if<String>()) {
        if (auto with = repl.find(*str); with != repl.end()) {
            json = with->second;
        }
    }
    if (auto array = json.get_if<Array>()) {
        for (auto& item: *array) {
            replace_json(item, repl);
        }
    }
    if (auto object = json.get_if<Object>()) {
        Object backup = {};
        for (auto i = object->begin(); i != object->end(); ) {
            replace_json(i->second, repl);
            if (auto with = repl.find(i->first); with != repl.end()) {
                if (auto str = with->second.get_if<String>()) {
                    backup[*str] = std::move(i->second);
                    i = object->erase(i);
                } else {
                    throw std::runtime_error("Tried to replace object key with non-string!");
                }
            } else {
                ++i;
            }
        }
        for (auto& [key, value]: backup) {
            (*object)[key] = std::move(value);
        }
    }
}

std::vector<PKT_S2C> pkts_from_json(Json& json, Json const& repls) {
    if (auto repls_obj = repls.get_if<Object>()) {
        replace_json(json, *repls_obj);
    }
    if (Logger::currentLevel >= LLOG_TRACE) {
        LOG_TRACE("Parsing packets: %s", (char const*)json.dumps(0).c_str());
    }
    if (json.is<Object>()) {
        return std::vector<PKT_S2C> { json.into<PKT_S2C>() };
    } else {
        return json.into<std::vector<PKT_S2C>>();
    }
}
