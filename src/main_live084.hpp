#pragma once
#include <string>
#include <enet/enet.h>
#include "r3d/r3d.hpp"

enum pkttype_e
{
    PKT_Dummy = 0,
    PKT_C2S_ClientConnect_NamedPipe = 1u,
    PKT_CHAT = 2u,
    PKT_C2S_QueryStatusReq = 3u,
    PKT_S2C_QueryStatusAns = 4u,
    PKT_S2C_StartSpawn = 5u,
    PKT_S2C_CreateHero = 6u,
    PKT_S2C_CreateNeutral = 7u,
    PKT_S2C_CreateTurret = 8u,
    PKT_S2C_PlayAnimation = 9u,
    PKT_C2S_PlayEmote = 0xAu,
    PKT_S2C_PlayEmote = 0xBu,
    PKT_S2C_EndSpawn = 0xCu,
    PKT_S2C_StartGame = 0xDu,
    PKT_S2C_EndGame = 0xEu,
    PKT_C2S_CharSelected = 0xFu,
    PKT_C2S_ClientReady = 0x10u,
    PKT_C2S_ClientFinished = 0x11u,
    PKT_NPC_UpgradeSpellReq = 0x12u,
    PKT_NPC_UpgradeSpellAns = 0x13u,
    PKT_NPC_IssueOrderReq = 0x14u,
    PKT_FX_Create_Group = 0x15u,
    PKT_FX_Kill = 0x16u,
    PKT_UnitApplyDamage = 0x17u,
    PKT_Pause = 0x18u,
    PKT_C2S_MapPing = 0x19u,
    PKT_S2C_MapPing = 0x1Au,
    PKT_UnitAddGold = 0x1Bu,
    PKT_UnitAddEXP = 0x1Cu,
    PKT_UserMessagesStart = 0x1Du,
    PKT_NPC_MessageToClient = 0x1Eu,
    PKT_AI_Command = 0x1Fu,
    PKT_CHAR_SpawnPet = 0x20u,
    PKT_CHAR_SetCooldown = 0x21u,
    PKT_NPC_Die = 0x22u,
    PKT_NPC_CastSpellReq = 0x23u,
    PKT_NPC_CastSpellAns = 0x24u,
    PKT_NPC_BuffAdd2 = 0x25u,
    PKT_NPC_BuffAddGroup = 0x26u,
    PKT_NPC_BuffReplace = 0x27u,
    PKT_NPC_BuffReplaceGroup = 0x28u,
    PKT_NPC_BuffRemove2 = 0x29u,
    PKT_NPC_BuffRemoveGroup = 0x2Au,
    PKT_NPC_SetAutocast = 0x2Bu,
    PKT_BuyItemReq = 0x2Cu,
    PKT_BuyItemAns = 0x2Du,
    PKT_RemoveItemReq = 0x2Eu,
    PKT_RemoveItemAns = 0x2Fu,
    PKT_SwapItemReq = 0x30u,
    PKT_SwapItemAns = 0x31u,
    PKT_UseItemAns = 0x32u,
    PKT_NPC_LevelUp = 0x33u,
    PKT_NPC_InstantStop_Attack = 0x34u,
    PKT_Barrack_SpawnUnit = 0x35u,
    PKT_Turret_Fire = 0x36u,
    PKT_Turret_CreateTurret = 0x37u,
    pkt32 = 0x38u,
    PKT_Basic_Attack = 0x39u,
    PKT_Basic_Attack_Pos = 0x3Au,
    PKT_OnEnterVisiblityClient = 0x3Bu,
    PKT_OnLeaveVisiblityClient = 0x3Cu,
    PKT_OnEnterLocalVisiblityClient = 0x3Du,
    PKT_OnLeaveLocalVisiblityClient = 0x3Eu,
    PKT_World_SendCamera_Server = 0x3Fu,
    PKT_World_LockCamera_Server = 0x40u,
    PKT_SendSelectedObjID = 0x41u,
    PKT_UnitApplyHeal = 0x42u,
    PKT_MissileReplication = 0x43u,
    PKT_ServerTick = 0x44u,
    PKT_DampenerSwitch = 0x45u,
    PKT_GlobalCombatMessage = 0x46u,
    PKT_SynchVersionC2S = 0x47u,
    PKT_SynchVersionS2C = 0x48u,
    PKT_AI_TargetS2C = 0x49u,
    PKT_AI_TargetHeroS2C = 0x4Au,
    PKT_SPM_HierarchicalProfilerUpdate = 0x4Bu,
    PKT_SPM_HierarchicalMemoryUpdate = 0x4Cu,
    PKT_SPM_HierarchicalBBProfileUpdate = 0x4Du,
    PKT_SPM_SamplingProfilerUpdate = 0x4Eu,
    PKT_SPM_AddBBProfileListener = 0x4Fu,
    PKT_SPM_RemoveBBProfileListener = 0x50u,
    PKT_HeroReincarnateAlive = 0x51u,
    PKT_HeroReincarnate = 0x52u,
    PKT_Building_Die = 0x53u,
    PKT_SynchSimTimeS2C = 0x54u,
    PKT_SynchSimTimeC2S = 0x55u,
    PKT_SyncSimTimeFinalS2C = 0x56u,
    PKT_WaypointList = 0x57u,
    PKT_WaypointListHeroWithSpeed = 0x58u,
    PKT_ServerGameSettings = 0x59u,
    PKT_NPC_BuffUpdateCount = 0x5Au,
    PKT_NPC_BuffUpdateCountGroup = 0x5Bu,
    PKT_C2S_PlayEmoticon = 0x5Cu,
    PKT_S2C_PlayEmoticon = 0x5Du,
    PKT_AvatarInfo_Server = 0x5Eu,
    PKT_RemovePerceptionBubble = 0x5Fu,
    PKT_AddUnitPerceptionBubble = 0x60u,
    PKT_AddPosPerceptionBubble = 0x61u,
    PKT_SpawnMinionS2C = 0x62u,
    PKT_S2C_StopAnimation = 0x63u,
    PKT_UpdateGoldRedirectTarget = 0x64u,
    PKT_S2C_ChangeCharacterData = 0x65u,
    PKT_S2C_PopCharacterData = 0x66u,
    PKT_S2C_PopAllCharacterData = 0x67u,
    PKT_S2C_FaceDirection = 0x68u,
    PKT_S2C_CameraBehavior = 0x69u,
    PKT_SPM_AddListener = 0x6Au,
    PKT_SPM_RemoveListener = 0x6Bu,
    PKT_SPM_AddMemoryListener = 0x6Cu,
    PKT_SPM_RemoveMemoryListener = 0x6Du,
    PKT_S2C_DestroyClientMissile = 0x6Eu,
    PKT_S2C_ChainMissileSync = 0x6Fu,
    PKT_MissileReplication_ChainMissile = 0x70u,
    PKT_S2C_BotAI = 0x71u,
    PKT_S2C_AI_TargetSelection = 0x72u,
    PKT_S2C_AI_State = 0x73u,
    PKT_OnEvent = 0x74u,
    PKT_OnDisconnected = 0x75u,
    PKT_World_SendCamera_Server_Acknologment = 0x76u,
    PKT_World_SendGameNumber = 0x77u,
    PKT_NPC_Die_EventHistroy = 0x78u,
    PKT_C2S_Ping_Load_Info = 0x79u,
    PKT_S2C_Ping_Load_Info = 0x7Au,
    PKT_C2S_Exit = 0x7Bu,
    PKT_S2C_Exit = 0x7Cu,
    PKT_C2S_Reconnect = 0x7Du,
    PKT_S2C_Reconnect = 0x7Eu,
    PKT_S2C_Reconnect_Done = 0x7Fu,
    PKT_Waypoint_Acc = 0x80u,
    PKT_WaypointGroup = 0x81u,
    PKT_WaypointGroupWithSpeed = 0x82u,
    PKT_Connected = 0x83u,
    PKT_S2C_ToggleInputLockingFlag = 0x84u,
    PKT_S2C_ToggleFoW = 0x85u,
    PKT_S2C_SetCircularCameraRestriction = 0x86u,
    PKT_S2C_LockCamera = 0x87u,
    PKT_OnReplication = 0x88u,
    PKT_OnReplication_Acc = 0x89u,
    PKT_S2C_MoveCameraToPoint = 0x8Au,
    PKT_S2C_PlayTutorialAudioEvent = 0x8Bu,
    PKT_ChangeSlotSpellType = 0x8Cu,
    PKT_PausePacket = 0x8Du,
    PKT_ResumePacket = 0x8Eu,
    PKT_SetFrequency = 0x8Fu,
    PKT_SetFadeOut_Push = 0x90u,
    PKT_SetFadeOut_Pop = 0x91u,
    PKT_S2C_CreateUnitHighlight = 0x92u,
    PKT_S2C_RemoveUnitHighlight = 0x93u,
    PKT_S2C_OpenTutorialPopup = 0x94u,
    PKT_C2S_OnTutorialPopupClosed = 0x95u,
    PKT_S2C_OpenAFKWarningMessage = 0x96u,
    PKT_S2C_CloseShop = 0x97u,
    PKT_S2C_SetInputLockingFlag = 0x98u,
    PKT_C2S_OnShopOpened = 0x99u,
    PKT_S2C_ShowObjectiveText = 0x9Au,
    PKT_S2C_HideObjectiveText = 0x9Bu,
    PKT_S2C_RefreshObjectiveText = 0x9Cu,
    PKT_S2C_ShowAuxiliaryText = 0x9Du,
    PKT_S2C_HideAuxiliaryText = 0x9Eu,
    PKT_S2C_RefreshAuxiliaryText = 0x9Fu,
    PKT_S2C_HighlightHUDElement = 0xA0u,
    PKT_S2C_HighlightShopElement = 0xA1u,
    PKT_C2S_TeamSurrenderVote = 0xA2u,
    PKT_S2C_TeamSurrenderVote = 0xA3u,
    PKT_S2C_TeamSurrenderCountDown = 0xA4u,
    PKT_S2C_TeamSurrenderStatus = 0xA5u,
    PKT_S2C_LineMissileHitList = 0xA6u,
    PKT_C2S_TutorialAudioEventFinished = 0xA7u,
    PKT_S2C_HighlightTitanBarElement = 0xA8u,
    PKT_S2C_ToggleUIHighlight = 0xA9u,
    PKT_S2C_DisplayLocalizedTutorialChatText = 0xAAu,
    PKT_S2C_ToolTipVars = 0xABu,
    PKT_S2C_MuteVolumeCategory = 0xACu,
    PKT_S2C_OnEventWorld = 0xADu,
    PKT_S2C_AnimatedBuildingSetCurrentSkin = 0xAEu,
    PKT_S2C_SetGreyscaleEnabledWhenDead = 0xAFu,
    PKT_S2C_DisableHUDForEndOfGame = 0xB0u,
    PKT_ChangeSlotSpellName = 0xB1u,
    PKT_S2C_SwitchNexusesToOnIdleParticles = 0xB2u,
    PKT_S2C_FadeMinions = 0xB3u,
    PKT_S2C_FadeOutMainSFX = 0xB4u,
    PKT_S2C_HeroStats = 0xB5u,
    PKT_S2C_SetAnimStates = 0xB6u,
    PKT_ClientCheatDetectionSignal = 0xB7u,
    PKT_S2C_AddDebugCircle = 0xB8u,
    PKT_S2C_RemoveDebugCircle = 0xB9u,
    PKT_S2C_ModifyDebugCircleRadius = 0xBAu,
    PKT_S2C_ModifyDebugCircleColor = 0xBBu,
    PKT_Undefined = 0xBCu,
    PKT_Batched = 0xFFu,
    PKT_UpperLimitForPacketIDs = 0x100,
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

#pragma pack(push, 1)
template<uint8_t ID, uint32_t FLAG>
struct DefaultPacket : BasePacket<CHANNEL_GENERIC_APP_BROADCAST, FLAG>
{
    uint8_t eventID = ID;
    uint32_t fromID = {};
};

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
    uint8 spawnPosIndex = {};
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
    char mMapMode[128] = {};
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
