#pragma once
#include <string>
#include <enet/enet.h>
#include "r3d/r3d.hpp"

enum pkttype_e
{
    PKT_Dummy = 0x0,
    PKT_C2S_QueryStatusReq = 0x03,
    PKT_S2C_QueryStatusAns = 0x04,
    PKT_S2C_StartSpawn = 0x05,
    PKT_S2C_CreateHero = 0x06,
    PKT_S2C_CreateNeutral = 0x07,
    PKT_S2C_CreateTurret = 0x08,
    PKT_S2C_EndSpawn = 0x0C,
    PKT_S2C_StartGame = 0x0D,
    PKT_EndGame = 0x0E,
    PKT_C2S_CharSelected = 0x0F,
    PKT_C2S_ClientReady = 0x10,
    PKT_SynchVersionS2C = 0x48,
    PKT_SpawnMinionS2C = 0x5A,
    PKT_World_SendGameNumber = 0x71,
    PKT_NPC_IssueOrderReq = 0x14,
    PKT_WaypointList = 80,

    PKT_S2C_FaceDirection = 96,

    PKT_SynchVersionC2S = 0x47, // Guesed cuz - 1

    PKT_OnEnterVisiblityClient = 59,
    // PKT_OnEnterVisiblityClientLocal = 57,

    PKT_C2S_Ping_Load_Info = 0x56, // Guessed cuz - 1
    PKT_S2C_Ping_Load_Info = 0x57, // Tried from ida not sure
    // PKT_C2S_Ping_Load_Info = 0x72,
    // PKT_S2C_Ping_Load_Info = 0x73,

    PKT_S2C_Reconnect = 0x40 + 1,
    PKT_C2S_Reconnect = 0x40,
    // PKT_S2C_Reconnect = 0x99,
    // PKT_C2S_Reconnect = 0x98,
    // PKT_C2S_Reconnect = 0x72,
    // PKT_S2C_Reconnect = 0x73,

    PKT_Extended = 0x72,
};

enum egptype_e
{
    EGP_RequestJoinTeam = 0x64,
    EGP_RequestReskin = 0x65,
    EGP_RequestRename = 0x66,
    EGP_TeamRosterUpdate = 0x67,
    EGP_Chat = 0x68,
    EGP_sendToServer = 0x69,
    EGP_broadcastToClients = 0x6A,
};

enum EnetChannels
{
    CHANNEL_DEFAULT = 0x0,
    CHANNEL_GENERIC_APP_TO_SERVER = 0x1,
    CHANNEL_SYNCHCLOCK = 0x2,
    CHANNEL_GENERIC_APP_BROADCAST = 0x3,
    CHANNEL_GENERIC_APP_BROADCAST_UNRELIABLE = 0x4,
    CHANNEL_MIDDLE_TIER_CHAT = 0x5,
    CHANNEL_MIDDLE_TIER_ROSTER = 0x6,
    CHANNEL_NUM_TOTAL = 0x7,
};

template<uint8_t CHANNEL, uint32_t FLAG>
struct BasePacket
{
    static inline constexpr uint32_t flag() noexcept {
        return FLAG;
    }
    static inline constexpr uint8_t channel() noexcept {
        return CHANNEL;
    }
};

template<uint8_t ID, uint32_t FLAG>
struct DefaultPayload : BasePacket<CHANNEL_MIDDLE_TIER_ROSTER, FLAG>
{
    uint8_t type = ID;
};

struct EGP_RequestJoinTeam_s : DefaultPayload<EGP_RequestJoinTeam, ENET_PACKET_FLAG_RELIABLE>
{
    int32_t Id_Player = {};
    uint32_t team = {};
};

struct EGP_RequestRename_s : DefaultPayload<EGP_RequestRename, ENET_PACKET_FLAG_RELIABLE>
{
    int64_t Id_Player = {};
    int skinID = {};
    uint32_t bufferLen = {};
    char buffer[128] = {};
};

struct EGP_RequestReskin_s : DefaultPayload<EGP_RequestReskin, ENET_PACKET_FLAG_RELIABLE>
{
    int64_t Id_Player = {};
    int skinID = {};
    uint32_t bufferLen = {};
    char buffer[128] = {};
};

struct EGP_TeamRosterUpdate_s : DefaultPayload<EGP_TeamRosterUpdate, ENET_PACKET_FLAG_RELIABLE>
{
    unsigned int teamsize_order = {};
    unsigned int teamsize_chaos = {};
    int64_t orderMembers[24] = {};
    int64_t chaosMembers[24] = {};
    unsigned int current_teamsize_order = {};
    unsigned int current_teamsize_chaos = {};
};

template<uint8_t ID, uint32_t FLAG>
struct DefaultPacket : BasePacket<CHANNEL_GENERIC_APP_BROADCAST, FLAG>
{
    uint16_t eventID = ID;
    uint16_t eventID2 = ID;
    uint32_t fromID = {};
};

#pragma pack(push, 1)
struct ConnectionInfo
{
    int32_t mClientID = {};
    int64_t mPlayerID = {};
    float mPercentage = {};
    float mETA = {};
    int32_t mCount : 16;
    uint32_t mPing : 15;
    uint32_t mPad : 1;
    uint8_t mReady : 1;
    char mState[0] = {};
};

struct PlayerLiteInfo
{
    int64_t ID = {};
    uint16_t summonorLevel = {};
    uint32_t summonorSpell1 = {};
    uint32_t summonorSpell2  = {};
};

struct PKT_C2S_CharSelected_s : public DefaultPacket<PKT_C2S_CharSelected, ENET_PACKET_FLAG_RELIABLE>
{
};

struct PKT_C2S_ClientReady_s : public DefaultPacket<PKT_C2S_ClientReady, ENET_PACKET_FLAG_RELIABLE>
{
};

struct PKT_C2S_Ping_Load_Info_s : public DefaultPacket<PKT_C2S_Ping_Load_Info, ENET_PACKET_FLAG_RELIABLE>
{
    ConnectionInfo mConnectionInfo = {};
};

struct PKT_C2S_QueryStatusReq_s : public DefaultPacket<PKT_C2S_QueryStatusReq, ENET_PACKET_FLAG_RELIABLE>
{
};

struct PKT_C2S_Reconnect_s : public DefaultPacket<PKT_C2S_Reconnect, ENET_PACKET_FLAG_RELIABLE>
{
    bool isFullReconnect = {};
};

struct PKT_NPC_IssueOrderReq_s : public DefaultPacket<PKT_NPC_IssueOrderReq, ENET_PACKET_FLAG_RELIABLE>
{
    uint8_t order = {};
    r3dPoint3D pos = {};
    uint32_t targetNetID = {};
};

struct PKT_OnEnterVisiblityClient_s : public DefaultPacket<PKT_OnEnterVisiblityClient, ENET_PACKET_FLAG_RELIABLE>
{
};

struct PKT_S2C_CreateHero_s : public DefaultPacket<PKT_S2C_CreateHero, ENET_PACKET_FLAG_RELIABLE>
{
    uint32_t netObjID = {};
    uint8_t netNodeID = {};
    uint32_t playerUID = {};
    bool teamIsOrder = {};
    bool isBot = {};
    char Name[40] = {};
    char Skin[40] = {};
};

struct PKT_S2C_CreateTurret_s : public DefaultPacket<PKT_S2C_CreateTurret, ENET_PACKET_FLAG_RELIABLE>
{
    uint32_t netObjID = {};
    uint8_t netNodeID = {};
    char Name[64] = {};
};

struct PKT_S2C_EndSpawn_s : public DefaultPacket<PKT_S2C_EndSpawn, ENET_PACKET_FLAG_RELIABLE>
{
};

struct PKT_S2C_Ping_Load_Info_s : public DefaultPacket<PKT_S2C_Ping_Load_Info, ENET_PACKET_FLAG_RELIABLE>
{
    ConnectionInfo mConnectionInfo = {};
};

struct PKT_S2C_QueryStatusAns_s : public DefaultPacket<PKT_S2C_QueryStatusAns, ENET_PACKET_FLAG_RELIABLE>
{
    bool ok = {};
};

struct PKT_S2C_Reconnect_s : public DefaultPacket<PKT_S2C_Reconnect, ENET_PACKET_FLAG_RELIABLE>
{
    int32_t cid = {};
};

struct PKT_S2C_StartGame_s : public DefaultPacket<PKT_S2C_StartGame, ENET_PACKET_FLAG_RELIABLE>
{
};

struct PKT_S2C_StartSpawn_s : public DefaultPacket<PKT_S2C_StartSpawn, ENET_PACKET_FLAG_RELIABLE>
{
    uint8_t numBotsOrder = {};
    uint8_t numBotsChaos = {};
};

struct PKT_SynchVersionC2S_s : public DefaultPacket<PKT_SynchVersionC2S, ENET_PACKET_FLAG_RELIABLE>
{
    float mTime_LastClient = {};
    uint32_t mClientNetID = {};
    char mVersionString[256] = {};
};

struct PKT_SynchVersionS2C_s : public DefaultPacket<PKT_SynchVersionS2C, ENET_PACKET_FLAG_RELIABLE>
{
    bool mIsVersionOk = {};
    int mMapToLoad = {};
    PlayerLiteInfo playerInfo[12] = {};
    char mVersionString[256] = {};
};

struct PKT_WaypointList_s : public DefaultPacket<PKT_WaypointList, ENET_PACKET_FLAG_RELIABLE>
{
    uint32_t syncID = {};
};

struct PKT_S2C_FaceDirection_s : public DefaultPacket<PKT_S2C_FaceDirection, ENET_PACKET_FLAG_RELIABLE>
{
    r3dPoint3D direction = {};
};
#pragma pack(pop)
