#pragma once
#include <string>
#include <enet/enet.h>
#include "r3d/r3d.hpp"

enum pkttype_e
{
    PKT_Dummy = 0x0,
    PKT_SPM_HierarchicalProfilerUpdate = 0x1,
    PKT_S2C_DisplayLocalizedTutorialChatText = 0x2,
    PKT_Barrack_SpawnUnit = 0x3,
    PKT_S2C_SwitchNexusesToOnIdleParticles = 0x4,
    PKT_C2S_TutorialAudioEventFinished = 0x5,
    PKT_S2C_SetCircularMovementRestriction = 0x6,
    PKT_UpdateGoldRedirectTarget = 0x7,
    PKT_SynchSimTimeC2S = 0x8,
    PKT_RemoveItemReq = 0x9,
    PKT_ResumePacket = 0xA,
    PKT_RemoveItemAns = 0xB,
    pkt32 = 0xC,
    PKT_Basic_Attack = 0xD,
    PKT_S2C_RefreshObjectiveText = 0xE,
    PKT_S2C_CloseShop = 0xF,
    PKT_S2C_Reconnect = 0x10,
    PKT_UnitAddEXP = 0x11,
    PKT_S2C_EndSpawn = 0x12,
    PKT_SetFrequency = 0x13,
    PKT_S2C_HighlightTitanBarElement = 0x14,
    PKT_S2C_BotAI = 0x15,
    PKT_S2C_TeamSurrenderCountDown = 0x16,
    PKT_C2S_QueryStatusReq = 0x17,
    PKT_NPC_UpgradeSpellAns = 0x18,
    PKT_C2S_Ping_Load_Info = 0x19,
    PKT_ChangeSlotSpellType = 0x1A,
    PKT_NPC_MessageToClient = 0x1B,
    PKT_Basic_Attack_Pos = 0x1C,
    PKT_NPC_ForceDead = 0x1D,
    PKT_NPC_BuffUpdateCount = 0x1E,
    PKT_NPC_BuffReplaceGroup = 0x20,
    PKT_NPC_SetAutocast = 0x21,
    PKT_SwapItemReq = 0x22,
    PKT_NPC_Die_EventHistroy = 0x23,
    PKT_UnitAddGold = 0x24,
    PKT_AddUnitPerceptionBubble = 0x25,
    PKT_S2C_MoveCameraToPoint = 0x26,
    PKT_S2C_LineMissileHitList = 0x27,
    PKT_S2C_MuteVolumeCategory = 0x28,
    PKT_ServerTick = 0x29,
    PKT_S2C_StopAnimation = 0x2A,
    PKT_AvatarInfo_Server = 0x2B,
    PKT_DampenerSwitch = 0x2C,
    PKT_World_SendCamera_Server_Acknologment = 0x2D,
    PKT_S2C_ModifyDebugCircleRadius = 0x2E,
    PKT_World_SendCamera_Server = 0x2F,
    PKT_HeroReincarnateAlive = 0x30,
    PKT_NPC_BuffReplace = 0x31,
    PKT_Pause = 0x32,
    PKT_SetFadeOut_Pop = 0x33,
    PKT_ChangeSlotSpellName = 0x34,
    PKT_RemovePerceptionBubble = 0x36,
    PKT_NPC_InstantStop_Attack = 0x37,
    PKT_OnLeaveLocalVisiblityClient = 0x38,
    PKT_S2C_ShowObjectiveText = 0x39,
    PKT_CHAR_SpawnPet = 0x3A,
    PKT_FX_Kill = 0x3B,
    PKT_NPC_UpgradeSpellReq = 0x3C,
    PKT_Turret_CreateTurret = 0x3D,
    PKT_MissileReplication = 0x3E,
    PKT_S2C_HighlightHUDElement = 0x40,
    PKT_SwapItemAns = 0x41,
    PKT_NPC_LevelUp = 0x42,
    PKT_S2C_MapPing = 0x43,
    PKT_S2C_PlayEmote = 0x45,
    PKT_S2C_Reconnect_Done = 0x46,
    PKT_S2C_OnEventWorld = 0x47,
    PKT_S2C_HeroStats = 0x48,
    PKT_C2S_PlayEmote = 0x49,
    PKT_HeroReincarnate = 0x4A,
    PKT_S2C_CreateHero = 0x4C,
    PKT_SPM_AddMemoryListener = 0x4D,
    PKT_SPM_HierarchicalMemoryUpdate = 0x4E,
    PKT_S2C_ToggleUIHighlight = 0x4F,
    PKT_S2C_FaceDirection = 0x50,
    PKT_OnLeaveVisiblityClient = 0x51,
    PKT_C2S_ClientReady = 0x52,
    PKT_SynchVersionS2C = 0x54,
    PKT_S2C_HandleTipUpdate = 0x55,
    PKT_C2S_MapPing = 0x56,
    PKT_S2C_RemoveDebugCircle = 0x57,
    PKT_S2C_CreateUnitHighlight = 0x58,
    PKT_S2C_DestroyClientMissile = 0x59,
    PKT_S2C_StartGame = 0x5B,
    PKT_C2S_OnShopOpened = 0x5C,
    PKT_S2C_FadeOutMainSFX = 0x5E,
    PKT_UserMessagesStart = 0x5F,
    PKT_WaypointGroup = 0x60,
    PKT_S2C_StartSpawn = 0x61,
    PKT_S2C_CreateNeutral = 0x62,
    PKT_WaypointGroupWithSpeed = 0x63,
    PKT_UnitApplyDamage = 0x64,
    PKT_ModifyShield = 0x65,
    PKT_S2C_PopCharacterData = 0x66,
    PKT_NPC_BuffAddGroup = 0x67,
    PKT_S2C_AI_TargetSelection = 0x68,
    PKT_AI_TargetS2C = 0x69,
    PKT_S2C_SetAnimStates = 0x6A,
    PKT_S2C_ChainMissileSync = 0x6B,
    PKT_C2S_OnTipEvent = 0x6C,
    PKT_MissileReplication_ChainMissile = 0x6D,
    PKT_BuyItemAns = 0x6E,
    PKT_NPC_IssueOrderReq = 0x70,
    PKT_S2C_CameraBehavior = 0x71,
    PKT_S2C_AnimatedBuildingSetCurrentSkin = 0x72,
    PKT_Connected = 0x73,
    PKT_SyncSimTimeFinalS2C = 0x74,
    PKT_Waypoint_Acc = 0x75,
    PKT_AddPosPerceptionBubble = 0x76,
    PKT_S2C_LockCamera = 0x77,
    PKT_S2C_PlayVOAudioEvent = 0x78,
    PKT_AI_Command = 0x79,
    PKT_NPC_BuffRemove2 = 0x7A,
    PKT_SpawnMinionS2C = 0x7B,
    PKT_ClientCheatDetectionSignal = 0x7C,
    PKT_S2C_ToggleFoW = 0x7D,
    PKT_S2C_ToolTipVars = 0x7E,
    PKT_UnitApplyHeal = 0x7F,
    PKT_GlobalCombatMessage = 0x80,
    PKT_World_LockCamera_Server = 0x81,
    PKT_SetItem = 0x82,
    PKT_BuyItemReq = 0x82,
    PKT_WaypointListHeroWithSpeed = 0x83,
    PKT_S2C_SetInputLockingFlag = 0x84,
    PKT_CHAR_SetCooldown = 0x85,
    PKT_FX_Create_Group = 0x86,
    PKT_S2C_QueryStatusAns = 0x87,
    PKT_Building_Die = 0x88,
    PKT_SPM_RemoveListener = 0x89,
    PKT_S2C_HandleQuestUpdate = 0x8A,
    PKT_C2S_ClientFinished = 0x8B,
    PKT_CHAT = 0x8C,
    PKT_SPM_RemoveMemoryListener = 0x8D,
    PKT_C2S_Exit = 0x8E,
    PKT_ServerGameSettings = 0x8F,
    PKT_S2C_ModifyDebugCircleColor = 0x90,
    PKT_SPM_AddListener = 0x91,
    PKT_World_SendGameNumber = 0x92,
    PKT_C2S_ClientConnect_NamedPipe = 0x94,
    PKT_NPC_BuffRemoveGroup = 0x95,
    PKT_Turret_Fire = 0x96,
    PKT_S2C_Ping_Load_Info = 0x97,
    PKT_S2C_ChangeCharacterData = 0x98,
    PKT_S2C_Exit = 0x99,
    PKT_SPM_RemoveBBProfileListener = 0x9A,
    PKT_NPC_CastSpellReq = 0x9B,
    PKT_S2C_ToggleInputLockingFlag = 0x9C,
    PKT_C2S_Reconnect = 0x9D,
    PKT_S2C_CreateTurret = 0x9E,
    PKT_NPC_Die = 0x9F,
    PKT_UseItemAns = 0xA0,
    PKT_S2C_ShowAuxiliaryText = 0xA1,
    PKT_PausePacket = 0xA2,
    PKT_S2C_HideObjectiveText = 0xA3,
    PKT_OnEvent = 0xA4,
    PKT_C2S_TeamSurrenderVote = 0xA5,
    PKT_S2C_TeamSurrenderStatus = 0xA6,
    PKT_SPM_AddBBProfileListener = 0xA7,
    PKT_S2C_HideAuxiliaryText = 0xA8,
    PKT_OnReplication_Acc = 0xA9,
    PKT_OnDisconnected = 0xAA,
    PKT_S2C_SetGreyscaleEnabledWhenDead = 0xAB,
    PKT_S2C_AI_State = 0xAC,
    PKT_S2C_SetFoWStatus = 0xAD,
    PKT_OnEnterLocalVisiblityClient = 0xAE,
    PKT_S2C_HighlightShopElement = 0xAF,
    PKT_SendSelectedObjID = 0xB0,
    PKT_S2C_PlayAnimation = 0xB1,
    PKT_S2C_RefreshAuxiliaryText = 0xB2,
    PKT_SetFadeOut_Push = 0xB3,
    PKT_S2C_OpenTutorialPopup = 0xB4,
    PKT_S2C_RemoveUnitHighlight = 0xB5,
    PKT_NPC_CastSpellAns = 0xB6,
    PKT_SPM_HierarchicalBBProfileUpdate = 0xB7,
    PKT_NPC_BuffAdd2 = 0xB8,
    PKT_S2C_OpenAFKWarningMessage = 0xB9,
    PKT_WaypointList = 0xBA,
    PKT_OnEnterVisiblityClient = 0xBB,
    PKT_S2C_AddDebugCircle = 0xBC,
    PKT_S2C_DisableHUDForEndOfGame = 0xBD,
    PKT_SynchVersionC2S = 0xBE,
    PKT_C2S_CharSelected = 0xBF,
    PKT_NPC_BuffUpdateCountGroup = 0xC0,
    PKT_AI_TargetHeroS2C = 0xC1,
    PKT_SynchSimTimeS2C = 0xC2,
    PKT_S2C_Neutral_Camp_Empty = 0xC3,
    PKT_OnReplication = 0xC4,
    PKT_S2C_EndGame = 0xC5,
    PKT_Undefined = 0xC6,
    PKT_SPM_SamplingProfilerUpdate = 0xC7,
    PKT_S2C_PopAllCharacterData = 0xC8,
    PKT_S2C_TeamSurrenderVote = 0xC9,
    PKT_S2C_HandleUIHighlight = 0xCA,
    PKT_S2C_FadeMinions = 0xCB,
    PKT_C2S_OnTutorialPopupClosed = 0xCC,
    PKT_C2S_OnQuestEvent = 0xCD,
    PKT_S2C_ShowHealthBar = 0xCE,
    PKT_SpawnLevelPropS2C = 0xD0,
    PKT_UpdateLevelPropS2C = 0xD1,
    PKT_S2C_HandleCapturePointUpdate = 0xD2,
    PKT_S2C_HandleGameScore = 0xD3,
    PKT_S2C_HandleRespawnPointUpdate = 0xD4,
    PKT_C2S_OnRespawnPointEvent = 0xD5,
    PKT_S2C_UnitChangeTeam = 0xD6,
    PKT_S2C_UnitSetMinimapIcon = 0xD7,
    PKT_S2C_ColorRemapFX = 0xD8,
    PKT_Batched = 0xFF,
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
    bool isBot = {};
    uint32_t teamId = {};
    char botName[28] = {};
    char skinName[28] = {};
    uint32_t botDifficulty = {};
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
    uint8 botRank = {};
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
