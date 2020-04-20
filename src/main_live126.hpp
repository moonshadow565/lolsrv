#pragma once
#include <string>
#include <enet/enet.h>
#include "r3d/r3d.hpp"

enum pkttype_e
{
    PKT_Unused_Dummy                             = 0x000,
    PKT_Unused_SPM_HierarchicalProfilerUpdate    = 0x001,
    PKT_S2C_DisplayLocalizedTutorialChatText     = 0x002,
    PKT_Barrack_SpawnUnit                        = 0x003,
    PKT_S2C_SwitchNexusesToOnIdleParticles       = 0x004,
    PKT_C2S_TutorialAudioEventFinished           = 0x005,
    PKT_S2C_SetCircularMovementRestriction       = 0x006,
    PKT_UpdateGoldRedirectTarget                 = 0x007,
    PKT_SynchSimTimeC2S                          = 0x008,
    PKT_RemoveItemReq                            = 0x009,
    PKT_ResumePacket                             = 0x00A,
    PKT_RemoveItemAns                            = 0x00B,
    PKT_Unused_PKT32                             = 0x00C,
    PKT_Basic_Attack                             = 0x00D,
    PKT_S2C_RefreshObjectiveText                 = 0x00E,
    PKT_S2C_CloseShop                            = 0x00F,
    PKT_S2C_Reconnect                            = 0x010,
    PKT_UnitAddEXP                               = 0x011,
    PKT_S2C_EndSpawn                             = 0x012,
    PKT_SetFrequency                             = 0x013,
    PKT_S2C_HighlightTitanBarElement             = 0x014,
    PKT_S2C_BotAI                                = 0x015,
    PKT_S2C_TeamSurrenderCountDown               = 0x016,
    PKT_C2S_QueryStatusReq                       = 0x017,
    PKT_NPC_UpgradeSpellAns                      = 0x018,
    PKT_C2S_Ping_Load_Info                       = 0x019,
    PKT_ChangeSlotSpellType                      = 0x01A,
    PKT_NPC_MessageToClient                      = 0x01B,
    PKT_DisplayFloatingText                      = 0x01C,
    PKT_Basic_Attack_Pos                         = 0x01D,
    PKT_NPC_ForceDead                            = 0x01E,
    PKT_NPC_BuffUpdateCount                      = 0x01F,
    PKT_C2S_WriteNavFlags_Acc                    = 0x020,
    PKT_NPC_BuffReplaceGroup                     = 0x021,
    PKT_NPC_SetAutocast                          = 0x022,
    PKT_SwapItemReq                              = 0x023,
    PKT_NPC_Die_EventHistroy                     = 0x024,
    PKT_UnitAddGold                              = 0x025,
    PKT_AddUnitPerceptionBubble                  = 0x026,
    PKT_S2C_MoveCameraToPoint                    = 0x027,
    PKT_S2C_LineMissileHitList                   = 0x028,
    PKT_S2C_MuteVolumeCategory                   = 0x029,
    PKT_ServerTick                               = 0x02A,
    PKT_S2C_StopAnimation                        = 0x02B,
    PKT_AvatarInfo_Server                        = 0x02C,
    PKT_DampenerSwitch                           = 0x02D,
    PKT_World_SendCamera_Server_Acknologment     = 0x02E,
    PKT_S2C_ModifyDebugCircleRadius              = 0x02F,
    PKT_World_SendCamera_Server                  = 0x030,
    PKT_HeroReincarnateAlive                     = 0x031,
    PKT_NPC_BuffReplace                          = 0x032,
    PKT_Pause                                    = 0x033,
    PKT_SetFadeOut_Pop                           = 0x034,
    PKT_ChangeSlotSpellName                      = 0x035,
    PKT_ChangeSlotSpellIcon                      = 0x036,
    PKT_ChangeSlotSpellOffsetTarget              = 0x037,
    PKT_RemovePerceptionBubble                   = 0x038,
    PKT_NPC_InstantStop_Attack                   = 0x039,
    PKT_OnLeaveLocalVisiblityClient              = 0x03A,
    PKT_S2C_ShowObjectiveText                    = 0x03B,
    PKT_CHAR_SpawnPet                            = 0x03C,
    PKT_FX_Kill                                  = 0x03D,
    PKT_NPC_UpgradeSpellReq                      = 0x03E,
    PKT_UseObjectC2S                             = 0x03F,
    PKT_Turret_CreateTurret                      = 0x040,
    PKT_MissileReplication                       = 0x041,
    PKT_ResetForSlowLoader                       = 0x042,
    PKT_S2C_HighlightHUDElement                  = 0x043,
    PKT_SwapItemAns                              = 0x044,
    PKT_NPC_LevelUp                              = 0x045,
    PKT_S2C_MapPing                              = 0x046,
    PKT_S2C_WriteNavFlags                        = 0x047,
    PKT_S2C_PlayEmote                            = 0x048,
    PKT_S2C_Reconnect_Done                       = 0x049,
    PKT_S2C_OnEventWorld                         = 0x04A,
    PKT_S2C_HeroStats                            = 0x04B,
    PKT_C2S_PlayEmote                            = 0x04C,
    PKT_HeroReincarnate                          = 0x04D,
    PKT_C2S_OnScoreBoardOpened                   = 0x04E,
    PKT_S2C_CreateHero                           = 0x04F,
    PKT_Unused_SPM_AddMemoryListener             = 0x050,
    PKT_Unused_SPM_HierarchicalMemoryUpdate      = 0x051,
    PKT_S2C_ToggleUIHighlight                    = 0x052,
    PKT_S2C_FaceDirection                        = 0x053,
    PKT_OnLeaveVisiblityClient                   = 0x054,
    PKT_C2S_ClientReady                          = 0x055,
    PKT_SetItem                                  = 0x056,
    PKT_SynchVersionS2C                          = 0x057,
    PKT_S2C_HandleTipUpdate                      = 0x058,
    PKT_C2S_StatsUpdateReq                       = 0x059,
    PKT_C2S_MapPing                              = 0x05A,
    PKT_S2C_RemoveDebugCircle                    = 0x05B,
    PKT_S2C_CreateUnitHighlight                  = 0x05C,
    PKT_S2C_DestroyClientMissile                 = 0x05D,
    PKT_S2C_LevelUpSpell                         = 0x05E,
    PKT_S2C_StartGame                            = 0x05F,
    PKT_C2S_OnShopOpened                         = 0x060,
    PKT_NPC_Hero_Die                             = 0x061,
    PKT_S2C_FadeOutMainSFX                       = 0x062,
    PKT_UserMessagesStart                        = 0x063,
    PKT_WaypointGroup                            = 0x064,
    PKT_S2C_StartSpawn                           = 0x065,
    PKT_S2C_CreateNeutral                        = 0x066,
    PKT_WaypointGroupWithSpeed                   = 0x067,
    PKT_UnitApplyDamage                          = 0x068,
    PKT_ModifyShield                             = 0x069,
    PKT_S2C_PopCharacterData                     = 0x06A,
    PKT_NPC_BuffAddGroup                         = 0x06B,
    PKT_S2C_AI_TargetSelection                   = 0x06C,
    PKT_AI_TargetS2C                             = 0x06D,
    PKT_S2C_SetAnimStates                        = 0x06E,
    PKT_S2C_ChainMissileSync                     = 0x06F,
    PKT_C2S_OnTipEvent                           = 0x070,
    PKT_MissileReplication_ChainMissile          = 0x071,
    PKT_BuyItemAns                               = 0x072,
    PKT_S2C_SetSpellData                         = 0x073,
    PKT_S2C_PauseAnimation                       = 0x074,
    PKT_NPC_IssueOrderReq                        = 0x075,
    PKT_S2C_CameraBehavior                       = 0x076,
    PKT_S2C_AnimatedBuildingSetCurrentSkin       = 0x077,
    PKT_Connected                                = 0x078,
    PKT_SyncSimTimeFinalS2C                      = 0x079,
    PKT_Waypoint_Acc                             = 0x07A,
    PKT_AddPosPerceptionBubble                   = 0x07B,
    PKT_S2C_LockCamera                           = 0x07C,
    PKT_S2C_PlayVOAudioEvent                     = 0x07D,
    PKT_AI_Command                               = 0x07E,
    PKT_NPC_BuffRemove2                          = 0x07F,
    PKT_SpawnMinionS2C                           = 0x080,
    PKT_Unused_ClientCheatDetectionSignal        = 0x081,
    PKT_S2C_ToggleFoW                            = 0x082,
    PKT_S2C_ToolTipVars                          = 0x083,
    PKT_UnitApplyHeal                            = 0x084,
    PKT_GlobalCombatMessage                      = 0x085,
    PKT_World_LockCamera_Server                  = 0x086,
    PKT_BuyItemReq                               = 0x087,
    PKT_WaypointListHeroWithSpeed                = 0x088,
    PKT_S2C_SetInputLockingFlag                  = 0x089,
    PKT_CHAR_SetCooldown                         = 0x08A,
    PKT_CHAR_CancelTargetingReticle              = 0x08B,
    PKT_FX_Create_Group                          = 0x08C,
    PKT_S2C_QueryStatusAns                       = 0x08D,
    PKT_Building_Die                             = 0x08E,
    PKT_Unused_SPM_RemoveListener                = 0x08F,
    PKT_S2C_HandleQuestUpdate                    = 0x090,
    PKT_C2S_ClientFinished                       = 0x091,
    PKT_CHAT                                     = 0x092,
    PKT_Unused_SPM_RemoveMemoryListener          = 0x093,
    PKT_C2S_Exit                                 = 0x094,
    PKT_ServerGameSettings                       = 0x095,
    PKT_S2C_ModifyDebugCircleColor               = 0x096,
    PKT_Unused_SPM_AddListener                   = 0x097,
    PKT_World_SendGameNumber                     = 0x098,
    PKT_ChangePARColorOverride                   = 0x099,
    PKT_C2S_ClientConnect_NamedPipe              = 0x09A,
    PKT_NPC_BuffRemoveGroup                      = 0x09B,
    PKT_Turret_Fire                              = 0x09C,
    PKT_S2C_Ping_Load_Info                       = 0x09D,
    PKT_S2C_ChangeCharacterVoice                 = 0x09E,
    PKT_S2C_ChangeCharacterData                  = 0x09F,
    PKT_S2C_Exit                                 = 0x0A0,
    PKT_Unused_SPM_RemoveBBProfileListener       = 0x0A1,
    PKT_NPC_CastSpellReq                         = 0x0A2,
    PKT_S2C_ToggleInputLockingFlag               = 0x0A3,
    PKT_C2S_Reconnect                            = 0x0A4,
    PKT_S2C_CreateTurret                         = 0x0A5,
    PKT_NPC_Die                                  = 0x0A6,
    PKT_UseItemAns                               = 0x0A7,
    PKT_S2C_ShowAuxiliaryText                    = 0x0A8,
    PKT_PausePacket                              = 0x0A9,
    PKT_S2C_HideObjectiveText                    = 0x0AA,
    PKT_OnEvent                                  = 0x0AB,
    PKT_C2S_TeamSurrenderVote                    = 0x0AC,
    PKT_S2C_TeamSurrenderStatus                  = 0x0AD,
    PKT_Unused_SPM_AddBBProfileListener          = 0x0AE,
    PKT_S2C_HideAuxiliaryText                    = 0x0AF,
    PKT_OnReplication_Acc                        = 0x0B0,
    PKT_OnDisconnected                           = 0x0B1,
    PKT_S2C_SetGreyscaleEnabledWhenDead          = 0x0B2,
    PKT_S2C_AI_State                             = 0x0B3,
    PKT_S2C_SetFoWStatus                         = 0x0B4,
    PKT_OnEnterLocalVisiblityClient              = 0x0B5,
    PKT_S2C_HighlightShopElement                 = 0x0B6,
    PKT_SendSelectedObjID                        = 0x0B7,
    PKT_S2C_PlayAnimation                        = 0x0B8,
    PKT_S2C_RefreshAuxiliaryText                 = 0x0B9,
    PKT_SetFadeOut_Push                          = 0x0BA,
    PKT_S2C_OpenTutorialPopup                    = 0x0BB,
    PKT_S2C_RemoveUnitHighlight                  = 0x0BC,
    PKT_NPC_CastSpellAns                         = 0x0BD,
    PKT_Unused_SPM_HierarchicalBBProfileUpdate   = 0x0BE,
    PKT_NPC_BuffAdd2                             = 0x0BF,
    PKT_S2C_OpenAFKWarningMessage                = 0x0C0,
    PKT_WaypointList                             = 0x0C1,
    PKT_OnEnterVisiblityClient                   = 0x0C2,
    PKT_S2C_AddDebugCircle                       = 0x0C3,
    PKT_S2C_DisableHUDForEndOfGame               = 0x0C4,
    PKT_SynchVersionC2S                          = 0x0C5,
    PKT_C2S_CharSelected                         = 0x0C6,
    PKT_NPC_BuffUpdateCountGroup                 = 0x0C7,
    PKT_AI_TargetHeroS2C                         = 0x0C8,
    PKT_SynchSimTimeS2C                          = 0x0C9,
    PKT_SyncMissionStartTimeS2C                  = 0x0CA,
    PKT_S2C_Neutral_Camp_Empty                   = 0x0CB,
    PKT_OnReplication                            = 0x0CC,
    PKT_S2C_EndOfGameEvent                       = 0x0CD,
    PKT_S2C_EndGame                              = 0x0CE,
    PKT_Unused_Undefined                         = 0x0CF,
    PKT_Unused_SPM_SamplingProfilerUpdate        = 0x0D0,
    PKT_S2C_PopAllCharacterData                  = 0x0D1,
    PKT_S2C_TeamSurrenderVote                    = 0x0D2,
    PKT_S2C_HandleUIHighlight                    = 0x0D3,
    PKT_S2C_FadeMinions                          = 0x0D4,
    PKT_C2S_OnTutorialPopupClosed                = 0x0D5,
    PKT_C2S_OnQuestEvent                         = 0x0D6,
    PKT_S2C_ShowHealthBar                        = 0x0D7,
    PKT_SpawnBotS2C                              = 0x0D8,
    PKT_SpawnLevelPropS2C                        = 0x0D9,
    PKT_UpdateLevelPropS2C                       = 0x0DA,
    PKT_AttachFlexParticleS2C                    = 0x0DB,
    PKT_S2C_HandleCapturePointUpdate             = 0x0DC,
    PKT_S2C_HandleGameScore                      = 0x0DD,
    PKT_S2C_HandleRespawnPointUpdate             = 0x0DE,
    PKT_C2S_OnRespawnPointEvent                  = 0x0DF,
    PKT_S2C_UnitChangeTeam                       = 0x0E0,
    PKT_S2C_UnitSetMinimapIcon                   = 0x0E1,
    PKT_S2C_IncrementPlayerScore                 = 0x0E2,
    PKT_S2C_IncrementPlayerStat                  = 0x0E3,
    PKT_S2C_ColorRemapFX                         = 0x0E4,
    PKT_S2C_MusicCueCommand                      = 0x0E5,
    PKT_Unused_S2C_AntiBot                       = 0x0E6,
    PKT_Unused_S2C_AntiBotWriteLog               = 0x0E7,
    PKT_Unused_S2C_AntiBotKickOut                = 0x0E8,
    PKT_Unused_S2C_AntiBotBanPlayer              = 0x0E9,
    PKT_Unused_S2C_AntiBotTrojan                 = 0x0EA,
    PKT_Unused_S2C_AntiBotCloseClient            = 0x0EB,
    PKT_Unused_C2S_AntiBotDP                     = 0x0EC,
    PKT_Unused_ED                                = 0x0ED,
    PKT_S2C_OnEnterTeamVisiblity                 = 0x0EE,
    PKT_S2C_OnLeaveTeamVisiblity                 = 0x0EF,
    PKT_S2C_FX_OnEnterTeamVisiblity              = 0x0F0,
    PKT_S2C_FX_OnLeaveTeamVisiblity              = 0x0F1,
    PKT_ReplayOnly_GoldEarned                    = 0x0F2,
    PKT_ExtendedPacket                           = 0x0FE,
    PKT_Batch                                    = 0x0FF,
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
    uint32_t profileIconId = {};
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
    uint8_t tournamentEnabled : 1;
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
