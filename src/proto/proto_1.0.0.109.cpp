#include "proto_1.0.0.109.hpp"

using ProtoVer = PROTO_VER(1.0.0.109);

std::string_view ProtoVer::name() const { return "1.0.0.109"; }

Span<ProtoNameID const> ProtoVer::pkt_array() const {
    static ProtoNameID const info[] = {
        { "PKT_Dummy", 0x0 },
        { "PKT_C2S_ClientConnect_NamedPipe", 0x1 },
        { "PKT_CHAT", 0x2 },
        { "PKT_C2S_QueryStatusReq", 0x3 },
        { "PKT_S2C_QueryStatusAns", 0x4 },
        { "PKT_S2C_StartSpawn", 0x5 },
        { "PKT_S2C_CreateHero", 0x6 },
        { "PKT_S2C_CreateNeutral", 0x7 },
        { "PKT_S2C_CreateTurret", 0x8 },
        { "PKT_S2C_PlayAnimation", 0x9 },
        { "PKT_C2S_PlayEmote", 0xA },
        { "PKT_S2C_PlayEmote", 0xB },
        { "PKT_S2C_EndSpawn", 0xC },
        { "PKT_S2C_StartGame", 0xD },
        { "PKT_S2C_EndGame", 0xE },
        { "PKT_C2S_CharSelected", 0xF },
        { "PKT_C2S_ClientReady", 0x10 },
        { "PKT_C2S_ClientFinished", 0x11 },
        { "PKT_NPC_UpgradeSpellReq", 0x12 },
        { "PKT_NPC_UpgradeSpellAns", 0x13 },
        { "PKT_NPC_IssueOrderReq", 0x14 },
        { "PKT_FX_Create_Group", 0x15 },
        { "PKT_FX_Kill", 0x16 },
        { "PKT_UnitApplyDamage", 0x17 },
        { "PKT_Pause", 0x18 },
        { "PKT_C2S_MapPing", 0x19 },
        { "PKT_S2C_MapPing", 0x1A },
        { "PKT_UnitAddGold", 0x1B },
        { "PKT_UnitAddEXP", 0x1C },
        { "PKT_UserMessagesStart", 0x1D },
        { "PKT_NPC_MessageToClient", 0x1E },
        { "PKT_AI_Command", 0x1F },
        { "PKT_CHAR_SpawnPet", 0x20 },
        { "PKT_CHAR_SetCooldown", 0x21 },
        { "PKT_NPC_Die", 0x22 },
        { "PKT_NPC_ForceDead", 0x24 },
        { "PKT_NPC_CastSpellReq", 0x25 },
        { "PKT_NPC_CastSpellAns", 0x26 },
        { "PKT_NPC_BuffAdd2", 0x27 },
        { "PKT_NPC_BuffAddGroup", 0x28 },
        { "PKT_NPC_BuffReplace", 0x29 },
        { "PKT_NPC_BuffReplaceGroup", 0x2A },
        { "PKT_NPC_BuffRemove2", 0x2B },
        { "PKT_NPC_BuffRemoveGroup", 0x2C },
        { "PKT_NPC_SetAutocast", 0x2D },
        { "PKT_SetItem", 0x2F },
        { "PKT_BuyItemReq", 0x2F },
        { "PKT_BuyItemAns", 0x30 },
        { "PKT_RemoveItemReq", 0x31 },
        { "PKT_RemoveItemAns", 0x32 },
        { "PKT_SwapItemReq", 0x33 },
        { "PKT_SwapItemAns", 0x34 },
        { "PKT_UseItemAns", 0x35 },
        { "PKT_NPC_LevelUp", 0x36 },
        { "PKT_NPC_InstantStop_Attack", 0x37 },
        { "PKT_Barrack_SpawnUnit", 0x38 },
        { "PKT_Turret_Fire", 0x39 },
        { "PKT_Turret_CreateTurret", 0x3A },
        { "pkt32", 0x3B },
        { "PKT_Basic_Attack", 0x3C },
        { "PKT_Basic_Attack_Pos", 0x3D },
        { "PKT_OnEnterVisiblityClient", 0x3E },
        { "PKT_OnLeaveVisiblityClient", 0x3F },
        { "PKT_OnEnterLocalVisiblityClient", 0x40 },
        { "PKT_OnLeaveLocalVisiblityClient", 0x41 },
        { "PKT_World_SendCamera_Server", 0x42 },
        { "PKT_World_LockCamera_Server", 0x43 },
        { "PKT_SendSelectedObjID", 0x44 },
        { "PKT_UnitApplyHeal", 0x45 },
        { "PKT_MissileReplication", 0x46 },
        { "PKT_ServerTick", 0x47 },
        { "PKT_DampenerSwitch", 0x48 },
        { "PKT_GlobalCombatMessage", 0x49 },
        { "PKT_SynchVersionC2S", 0x4A },
        { "PKT_SynchVersionS2C", 0x4B },
        { "PKT_AI_TargetS2C", 0x4C },
        { "PKT_AI_TargetHeroS2C", 0x4D },
        { "PKT_SPM_HierarchicalProfilerUpdate", 0x4F },
        { "PKT_SPM_HierarchicalMemoryUpdate", 0x50 },
        { "PKT_SPM_HierarchicalBBProfileUpdate", 0x51 },
        { "PKT_SPM_SamplingProfilerUpdate", 0x52 },
        { "PKT_SPM_AddBBProfileListener", 0x53 },
        { "PKT_SPM_RemoveBBProfileListener", 0x54 },
        { "PKT_HeroReincarnateAlive", 0x55 },
        { "PKT_HeroReincarnate", 0x56 },
        { "PKT_Building_Die", 0x57 },
        { "PKT_SynchSimTimeS2C", 0x58 },
        { "PKT_SynchSimTimeC2S", 0x59 },
        { "PKT_SyncSimTimeFinalS2C", 0x5A },
        { "PKT_WaypointList", 0x5B },
        { "PKT_WaypointListHeroWithSpeed", 0x5C },
        { "PKT_ServerGameSettings", 0x5D },
        { "PKT_NPC_BuffUpdateCount", 0x5E },
        { "PKT_NPC_BuffUpdateCountGroup", 0x5F },
        { "PKT_C2S_PlayEmoticon", 0x60 },
        { "PKT_S2C_PlayEmoticon", 0x61 },
        { "PKT_AvatarInfo_Server", 0x62 },
        { "PKT_RemovePerceptionBubble", 0x63 },
        { "PKT_AddUnitPerceptionBubble", 0x64 },
        { "PKT_AddPosPerceptionBubble", 0x65 },
        { "PKT_SpawnMinionS2C", 0x66 },
        { "PKT_S2C_StopAnimation", 0x67 },
        { "PKT_S2C_ShowHealthBar", 0x68 },
        { "PKT_UpdateGoldRedirectTarget", 0x69 },
        { "PKT_S2C_ChangeCharacterData", 0x6A },
        { "PKT_S2C_PopCharacterData", 0x6B },
        { "PKT_S2C_PopAllCharacterData", 0x6C },
        { "PKT_S2C_FaceDirection", 0x6D },
        { "PKT_S2C_CameraBehavior", 0x6E },
        { "PKT_SPM_AddListener", 0x6F },
        { "PKT_SPM_RemoveListener", 0x70 },
        { "PKT_SPM_AddMemoryListener", 0x71 },
        { "PKT_SPM_RemoveMemoryListener", 0x72 },
        { "PKT_S2C_DestroyClientMissile", 0x73 },
        { "PKT_S2C_ChainMissileSync", 0x74 },
        { "PKT_MissileReplication_ChainMissile", 0x75 },
        { "PKT_S2C_BotAI", 0x76 },
        { "PKT_S2C_AI_TargetSelection", 0x77 },
        { "PKT_S2C_AI_State", 0x78 },
        { "PKT_OnEvent", 0x79 },
        { "PKT_OnDisconnected", 0x7A },
        { "PKT_World_SendCamera_Server_Acknologment", 0x7B },
        { "PKT_World_SendGameNumber", 0x7C },
        { "PKT_NPC_Die_EventHistroy", 0x7D },
        { "PKT_C2S_Ping_Load_Info", 0x7E },
        { "PKT_S2C_Ping_Load_Info", 0x7F },
        { "PKT_C2S_Exit", 0x80 },
        { "PKT_S2C_Exit", 0x81 },
        { "PKT_C2S_Reconnect", 0x82 },
        { "PKT_S2C_Reconnect", 0x83 },
        { "PKT_S2C_Reconnect_Done", 0x84 },
        { "PKT_Waypoint_Acc", 0x85 },
        { "PKT_WaypointGroup", 0x86 },
        { "PKT_WaypointGroupWithSpeed", 0x87 },
        { "PKT_Connected", 0x88 },
        { "PKT_S2C_ToggleInputLockingFlag", 0x89 },
        { "PKT_S2C_ToggleFoW", 0x8A },
        { "PKT_S2C_SetFoWStatus", 0x8B },
        { "PKT_S2C_SetCircularCameraRestriction", 0x8C },
        { "PKT_S2C_LockCamera", 0x8D },
        { "PKT_OnReplication", 0x8E },
        { "PKT_OnReplication_Acc", 0x8F },
        { "PKT_S2C_MoveCameraToPoint", 0x90 },
        { "PKT_S2C_HandleQuestUpdate", 0x91 },
        { "PKT_C2S_OnQuestEvent", 0x92 },
        { "PKT_S2C_HandleTipUpdate", 0x93 },
        { "PKT_S2C_HandleUIHighlight", 0x94 },
        { "PKT_C2S_OnTipEvent", 0x95 },
        { "PKT_S2C_PlayVOAudioEvent", 0x96 },
        { "PKT_ChangeSlotSpellType", 0x97 },
        { "PKT_PausePacket", 0x98 },
        { "PKT_ResumePacket", 0x99 },
        { "PKT_SetFrequency", 0x9A },
        { "PKT_SetFadeOut_Push", 0x9B },
        { "PKT_SetFadeOut_Pop", 0x9C },
        { "PKT_S2C_CreateUnitHighlight", 0x9D },
        { "PKT_S2C_RemoveUnitHighlight", 0x9E },
        { "PKT_S2C_OpenTutorialPopup", 0x9F },
        { "PKT_C2S_OnTutorialPopupClosed", 0xA0 },
        { "PKT_S2C_OpenAFKWarningMessage", 0xA1 },
        { "PKT_S2C_CloseShop", 0xA2 },
        { "PKT_S2C_SetInputLockingFlag", 0xA3 },
        { "PKT_C2S_OnShopOpened", 0xA4 },
        { "PKT_S2C_ShowObjectiveText", 0xA6 },
        { "PKT_S2C_HideObjectiveText", 0xA7 },
        { "PKT_S2C_RefreshObjectiveText", 0xA8 },
        { "PKT_S2C_ShowAuxiliaryText", 0xA9 },
        { "PKT_S2C_HideAuxiliaryText", 0xAA },
        { "PKT_S2C_RefreshAuxiliaryText", 0xAB },
        { "PKT_S2C_HighlightHUDElement", 0xAC },
        { "PKT_S2C_HighlightShopElement", 0xAD },
        { "PKT_C2S_TeamSurrenderVote", 0xAE },
        { "PKT_S2C_TeamSurrenderVote", 0xAF },
        { "PKT_S2C_TeamSurrenderCountDown", 0xB0 },
        { "PKT_S2C_TeamSurrenderStatus", 0xB1 },
        { "PKT_S2C_LineMissileHitList", 0xB2 },
        { "PKT_C2S_TutorialAudioEventFinished", 0xB3 },
        { "PKT_S2C_HighlightTitanBarElement", 0xB4 },
        { "PKT_S2C_ToggleUIHighlight", 0xB5 },
        { "PKT_S2C_DisplayLocalizedTutorialChatText", 0xB6 },
        { "PKT_S2C_ToolTipVars", 0xB7 },
        { "PKT_S2C_MuteVolumeCategory", 0xB8 },
        { "PKT_S2C_OnEventWorld", 0xB9 },
        { "PKT_S2C_AnimatedBuildingSetCurrentSkin", 0xBA },
        { "PKT_S2C_SetGreyscaleEnabledWhenDead", 0xBB },
        { "PKT_S2C_DisableHUDForEndOfGame", 0xBC },
        { "PKT_ChangeSlotSpellName", 0xBD },
        { "PKT_S2C_SwitchNexusesToOnIdleParticles", 0xBE },
        { "PKT_S2C_FadeMinions", 0xBF },
        { "PKT_S2C_FadeOutMainSFX", 0xC0 },
        { "PKT_S2C_HeroStats", 0xC1 },
        { "PKT_S2C_SetAnimStates", 0xC2 },
        { "PKT_ClientCheatDetectionSignal", 0xC3 },
        { "PKT_S2C_AddDebugCircle", 0xC4 },
        { "PKT_S2C_RemoveDebugCircle", 0xC5 },
        { "PKT_S2C_ModifyDebugCircleRadius", 0xC6 },
        { "PKT_S2C_ModifyDebugCircleColor", 0xC7 },
        { "PKT_Undefined", 0xC8 },
        { "PKT_S2C_Neutral_Camp_Empty", 0xC9 },
        { "PKT_Batched", 0xFF },
    };
    return info;
}
