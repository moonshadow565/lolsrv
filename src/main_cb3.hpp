#pragma once
#include <string>
#include <enet/enet.h>
#include "r3d/r3d.hpp"

enum pkttype_e
{
    PKT_Dummy = 0x0,
    PKT_C2S_ClientConnect_NamedPipe = 0x1,
    PKT_CHAT = 0x2,
    PKT_C2S_QueryStatusReq = 0x3,
    PKT_S2C_QueryStatusAns = 0x4,
    PKT_S2C_StartSpawn = 0x5,
    PKT_S2C_CreateHero = 0x6,
    PKT_S2C_CreateNeutral = 0x7,
    PKT_S2C_CreateTurret = 0x8,
    PKT_S2C_PlayAnimation = 0x9,
    PKT_C2S_PlayEmote = 0xA,
    PKT_S2C_PlayEmote = 0xB,
    PKT_S2C_EndSpawn = 0xC,
    PKT_S2C_StartGame = 0xD,
    PKT_S2C_EndGame = 0xE,
    PKT_C2S_CharSelected = 0xF,
    PKT_C2S_ClientReady = 0x10,
    PKT_C2S_ClientFinished = 0x11,
    PKT_NPC_UpgradeSpellReq = 0x12,
    PKT_NPC_UpgradeSpellAns = 0x13,
    PKT_NPC_IssueOrderReq = 0x14,
    PKT_FX_Create_Group = 0x15,
    PKT_FX_Kill = 0x16,
    PKT_UnitApplyDamage = 0x17,
    PKT_Pause = 0x18,
    PKT_C2S_MapPing = 0x19,
    PKT_S2C_MapPing = 0x1A,
    PKT_UnitAddGold = 0x1B,
    PKT_UnitAddEXP = 0x1C,
    PKT_UserMessagesStart = 0x1D,
    PKT_NPC_MessageToClient = 0x1E,
    PKT_AI_Command = 0x1F,
    PKT_CHAR_SpawnPet = 0x20,
    PKT_CHAR_SetCooldown = 0x21,
    PKT_NPC_Die = 0x22,
    PKT_NPC_CastSpellReq = 0x23,
    PKT_NPC_CastSpellAns = 0x24,
    PKT_NPC_BuffAdd2 = 0x25,
    PKT_NPC_BuffRenew = 0x26,
    PKT_NPC_BuffRemove2 = 0x27,
    PKT_NPC_SetAutocast = 0x28,
    PKT_BuyItemReq = 0x29,
    PKT_BuyItemAns = 0x2A,
    PKT_RemoveItemReq = 0x2B,
    PKT_RemoveItemAns = 0x2C,
    PKT_SwapItemReq = 0x2D,
    PKT_SwapItemAns = 0x2E,
    PKT_NPC_LevelUp = 0x2F,
    PKT_NPC_InstantStop_Attack = 0x30,
    PKT_Barrack_SpawnUnit = 0x31,
    PKT_Turret_Fire = 0x32,
    PKT_Turret_CreateTurret = 0x33,
    pkt32 = 0x34,
    PKT_Basic_Attack = 0x35,
    PKT_Basic_Attack_Pos = 0x36,
    PKT_OnEnterVisiblityClient = 0x37,
    PKT_OnLeaveVisiblityClient = 0x38,
    PKT_OnEnterLocalVisiblityClient = 0x39,
    PKT_OnLeaveLocalVisiblityClient = 0x3A,
    PKT_World_SendCamera_Server = 0x3B,
    PKT_World_LockCamera_Server = 0x3C,
    PKT_SendSelectedObjID = 0x3D,
    PKT_UnitApplyHeal = 0x3E,
    PKT_MissileReplication = 0x3F,
    PKT_ServerTick = 0x40,
    PKT_DampenerSwitch = 0x41,
    PKT_GlobalCombatMessage = 0x42,
    PKT_SynchVersionC2S = 0x43,
    PKT_SynchVersionS2C = 0x44,
    PKT_AI_TargetS2C = 0x45,
    PKT_AI_TargetHeroS2C = 0x46,
    // PKT_ReloadScripts = 0x47,
    // PKT_C2S_PlayAnimation = 0x64,
    // PKT_CheatDebugPoint = 0x66,
    // PKT_Cheat_Pause_Toggle = 0x67,
    // PKT_Cheat_IncTime = 0x68,
    // PKT_Cheat_DecTime = 0x69,
    PKT_HeroReincarnateAlive,
    PKT_HeroReincarnate,
    PKT_Building_Die,
    PKT_SynchSimTimeS2C,
    PKT_SynchSimTimeC2S,
    PKT_SyncSimTimeFinalS2C,
    PKT_WaypointList,
    PKT_WaypointListHeroWithSpeed,
    PKT_ServerGameSettings,
    PKT_NPC_BuffUpdateCount,
    PKT_C2S_PlayEmoticon,
    PKT_S2C_PlayEmoticon,
    PKT_AvatarInfo_Server,
    PKT_RemovePerceptionBubble,
    PKT_AddUnitPerceptionBubble,
    PKT_AddPosPerceptionBubble,
    PKT_SpawnMinionS2C,
    PKT_S2C_StopAnimation,
    PKT_UpdateGoldRedirectTarget,
    PKT_S2C_ChangeCharacterData,
    PKT_S2C_PopCharacterData,
    PKT_S2C_PopAllCharacterData,
    PKT_S2C_FaceDirection,
    PKT_S2C_CameraBehavior,
    PKT_SPM_AddListener,
    PKT_SPM_RemoveListener,
    PKT_SPM_HierarchicalProfilerUpdate,
    PKT_SPM_SamplingProfilerUpdate,
    PKT_SPM_HierarchicalMemoryUpdate,
    PKT_SPM_AddMemoryListener,
    PKT_SPM_RemoveMemoryListener,
    PKT_S2C_DestroyClientMissile,
    PKT_S2C_ChainMissileSync,
    PKT_MissileReplication_ChainMissile,
    PKT_S2C_BotAI,
    PKT_S2C_AI_TargetSelection,
    PKT_S2C_AI_State,
    PKT_OnEvent,
    PKT_OnDisconnected,
    PKT_World_SendCamera_Server_Acknologment,
    PKT_World_SendGameNumber,
    PKT_NPC_Die_EventHistroy,
    PKT_C2S_Ping_Load_Info,
    PKT_S2C_Ping_Load_Info,
    PKT_C2S_Exit,
    PKT_S2C_Exit,
    PKT_C2S_Reconnect,
    PKT_S2C_Reconnect,
    PKT_S2C_Reconnect_Done,
    PKT_Waypoint_Acc,
    PKT_WaypointGroup,
    PKT_WaypointGroupWithSpeed,
    PKT_Connected,
    PKT_C2S_ToggleInputLockingFlag,
    PKT_S2C_ToggleInputLockingFlag,
    PKT_S2C_ToggleFoW,
    PKT_S2C_SetCircularCameraRestriction,
    PKT_S2C_LockCamera,
    PKT_OnReplication,
    PKT_OnReplication_Acc,
    PKT_S2C_MoveCameraToPoint,
    PKT_S2C_PlayTutorialAudioEvent,
    PKT_ChangeSlotSpellType,
    PKT_PausePacket,
    PKT_ResumePacket,
    PKT_SetFrequency,
    PKT_SetFadeOut_Push,
    PKT_SetFadeOut_Pop,
    PKT_SPM_AddBBProfileListener,
    PKT_SPM_RemoveBBProfileListener,
    PKT_SPM_HierarchicalBBProfileUpdate,
    PKT_S2C_CreateUnitHighlight,
    PKT_S2C_RemoveUnitHighlight,
    PKT_S2C_OpenTutorialPopup,
    PKT_C2S_OnTutorialPopupClosed,
    PKT_S2C_OpenAFKWarningMessage,
    PKT_S2C_CloseShop,
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
    uint8_t eventID = ID;
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
    char mState[64] = {};
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
    uint32_t playerUID = {};
    uint8_t netNodeID = {};
    uint8_t skillLevel = {};
    bool teamIsOrder = {};
    bool isBot = {};
    int skinID = {};
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