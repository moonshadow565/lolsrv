#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>
#include <array>
#include <string>
#include <optional>
#include <variant>
#include <r3d.hpp>
#include <io.hpp>

enum Channel : uint32_t {
    CHANNEL_DEFAULT = 0x0,
    CHANNEL_GENERIC_APP_TO_SERVER = 0x1,
    CHANNEL_SYNCHCLOCK = 0x2,
    CHANNEL_GENERIC_APP_BROADCAST = 0x3,
    CHANNEL_GENERIC_APP_BROADCAST_UNRELIABLE = 0x4,
    CHANNEL_MIDDLE_TIER_CHAT = 0x5,
    CHANNEL_MIDDLE_TIER_ROSTER = 0x6,
    CHANNEL_NUM_TOTAL = 0x7,
};

enum class PKT_ID : uint16_t {};

enum class EGP_ID : uint16_t {};

struct DefaultPayload {};

struct EGP_RequestJoinTeam : public DefaultPayload {
    int32_t Id_Player = {};
    uint32_t team = {};
};

struct EGP_RequestRename : public DefaultPayload {
    int64_t Id_Player = {};
    int32_t skinID = {};
    std::string buffer = {};
};

struct EGP_RequestReskin : public DefaultPayload {
    int64_t Id_Player = {};
    int32_t skinID = {};
    std::string buffer = {};
};

struct EGP_TeamRosterUpdate : public DefaultPayload {
    uint32_t teamsize_order = {};
    uint32_t teamsize_chaos = {};
    int64_t orderMembers[24] = {};
    int64_t chaosMembers[24] = {};
    uint32_t current_teamsize_order = {};
    uint32_t current_teamsize_chaos = {};
};

struct ConnectionInfo {
    int32_t mClientID = {};
    int64_t mPlayerID = {};
    float mPercentage = {};
    float mETA = {};
    int16_t mCount = {};
    uint16_t mPing = {};
    uint8_t mPad = {};
    uint8_t mReady = {};
    std::string mState = {};
};

struct PlayerLiteInfo {
    int64_t ID = {};
    uint16_t summonorLevel = {};
    uint32_t summonorSpell1 = {};
    uint32_t summonorSpell2  = {};
    bool isBot = {};
    uint32_t teamId = {};
    std::string botName = {};
    std::string skinName = {};
    uint32_t botDifficulty = {};
    uint32_t profileIconId = {};
};

struct ItemData {
    uint32_t itemID = {};
    uint8_t slot = {};
    uint8_t itemsInSlot = {};
    uint8_t spellCharges = {};
};

struct DefaultPacket {};

struct PKT_C2S_CharSelected : public DefaultPacket {
    uint32_t fromID = {};
};

struct PKT_C2S_ClientReady : public DefaultPacket {
    uint32_t fromID = {};
};

struct PKT_C2S_Ping_Load_Info : public DefaultPacket {
    uint32_t fromID = {};
    ConnectionInfo mConnectionInfo = {};
};

struct PKT_C2S_QueryStatusReq : public DefaultPacket {
    uint32_t fromID = {};
};

struct PKT_C2S_Reconnect : public DefaultPacket {
    uint32_t fromID = {};
    bool isFullReconnect = {};
};

struct PKT_NPC_IssueOrderReq : public DefaultPacket {
    uint32_t fromID = {};
    uint8_t order = {};
    r3dPoint3D pos = {};
    uint32_t targetNetID = {};
};

struct PKT_OnEnterVisiblityClient : public DefaultPacket {
    uint32_t fromID = {};
    std::vector<ItemData> items = {};
    std::optional<r3dPoint3D> lookat = {};
    std::optional<r3dPoint2D> position = {};
    uint32_t syncId = {};
};

struct PKT_S2C_CreateHero : public DefaultPacket {
    uint32_t fromID = {};
    uint32_t netObjID = {};
    int32_t playerUID = {};
    uint8_t netNodeID = {};
    uint8_t skillLevel = {};
    bool teamIsOrder = {};
    bool isBot = {};
    uint8_t botRank = {};
    uint8_t spawnPosIndex = {};
    int32_t skinID = {};
    std::string Name = {};
    std::string Skin = {};
};

struct PKT_S2C_CreateTurret : public DefaultPacket {
    uint32_t fromID = {};
    uint32_t netObjID = {};
    uint8_t netNodeID = {};
    std::string Name = {};
};

struct PKT_S2C_EndSpawn : public DefaultPacket {
    uint32_t fromID = {};
};

struct PKT_S2C_Ping_Load_Info : public DefaultPacket {
    uint32_t fromID = {};
    ConnectionInfo mConnectionInfo = {};
};

struct PKT_S2C_QueryStatusAns : public DefaultPacket {
    uint32_t fromID = {};
    bool ok = {};
};

struct PKT_S2C_Reconnect : public DefaultPacket {
    uint32_t fromID = {};
    int32_t cid = {};
};

struct PKT_S2C_StartGame : public DefaultPacket {
    uint32_t fromID = {};
    uint8_t tournamentEnabled = {};
};

struct PKT_S2C_StartSpawn : public DefaultPacket {
    uint32_t fromID = {};
    uint8_t numBotsOrder = {};
    uint8_t numBotsChaos = {};
};

struct PKT_SynchVersionC2S : public DefaultPacket {
    uint32_t fromID = {};
    float mTime_LastClient = {};
    uint32_t mClientNetID = {};
    std::string mVersionString = {};
};

struct PKT_SynchVersionS2C : public DefaultPacket {
    uint32_t fromID = {};
    bool mIsVersionOk = {};
    int mMapToLoad = {};
    PlayerLiteInfo playerInfo[12] = {};
    std::string mVersionString = {};
    std::string mMapMode = {};
};

struct PKT_WaypointList : public DefaultPacket {
    uint32_t fromID = {};
    uint32_t syncID = {};
    std::vector<r3dPoint2D> list = {};
};

struct PKT_S2C_FaceDirection : public DefaultPacket {
    uint32_t fromID = {};
    r3dPoint3D direction = {};
};

using PKT_C2S = std::variant<
    EGP_RequestJoinTeam,
    PKT_C2S_CharSelected,
    PKT_C2S_ClientReady,
    PKT_C2S_Ping_Load_Info,
    PKT_C2S_QueryStatusReq,
    PKT_C2S_Reconnect,
    PKT_NPC_IssueOrderReq,
    PKT_SynchVersionC2S
>;

using PKT_S2C = std::variant<
    EGP_RequestRename,
    EGP_RequestReskin,
    EGP_TeamRosterUpdate,
    PKT_OnEnterVisiblityClient,
    PKT_S2C_CreateHero,
    PKT_S2C_CreateTurret,
    PKT_S2C_EndSpawn,
    PKT_S2C_Ping_Load_Info,
    PKT_S2C_QueryStatusAns,
    PKT_S2C_Reconnect,
    PKT_S2C_StartGame,
    PKT_S2C_StartSpawn,
    PKT_SynchVersionS2C,
    PKT_WaypointList,
    PKT_S2C_FaceDirection
>;

