#include "proto_1.0.0.131.hpp"

using ProtoVer = PROTO_VER(1.0.0.131);

std::string_view ProtoVer::name() const { return "1.0.0.131"; }

Span<ProtoNameID const> ProtoVer::pkt_array() const {
    static ProtoNameID const info[] = {
        { "PKT_Unused_Dummy", 0x0 },
        { "PKT_Unused_SPM_HierarchicalProfilerUpdate", 0x1 },
        { "PKT_S2C_DisplayLocalizedTutorialChatText", 0x2 },
        { "PKT_Barrack_SpawnUnit", 0x3 },
        { "PKT_S2C_SwitchNexusesToOnIdleParticles", 0x4 },
        { "PKT_C2S_TutorialAudioEventFinished", 0x5 },
        { "PKT_S2C_SetCircularMovementRestriction", 0x6 },
        { "PKT_UpdateGoldRedirectTarget", 0x7 },
        { "PKT_SynchSimTimeC2S", 0x8 },
        { "PKT_RemoveItemReq", 0x9 },
        { "PKT_ResumePacket", 0xA },
        { "PKT_RemoveItemAns", 0xB },
        { "PKT_Unused_PKT32", 0xC },
        { "PKT_Basic_Attack", 0xD },
        { "PKT_S2C_RefreshObjectiveText", 0xE },
        { "PKT_S2C_CloseShop", 0xF },
        { "PKT_S2C_Reconnect", 0x10 },
        { "PKT_UnitAddEXP", 0x11 },
        { "PKT_S2C_EndSpawn", 0x12 },
        { "PKT_SetFrequency", 0x13 },
        { "PKT_S2C_HighlightTitanBarElement", 0x14 },
        { "PKT_S2C_BotAI", 0x15 },
        { "PKT_S2C_TeamSurrenderCountDown", 0x16 },
        { "PKT_C2S_QueryStatusReq", 0x17 },
        { "PKT_NPC_UpgradeSpellAns", 0x18 },
        { "PKT_C2S_Ping_Load_Info", 0x19 },
        { "PKT_ChangeSlotSpellType", 0x1A },
        { "PKT_NPC_MessageToClient", 0x1B },
        { "PKT_DisplayFloatingText", 0x1C },
        { "PKT_Basic_Attack_Pos", 0x1D },
        { "PKT_NPC_ForceDead", 0x1E },
        { "PKT_NPC_BuffUpdateCount", 0x1F },
        { "PKT_C2S_WriteNavFlags_Acc", 0x20 },
        { "PKT_NPC_BuffReplaceGroup", 0x21 },
        { "PKT_NPC_SetAutocast", 0x22 },
        { "PKT_SwapItemReq", 0x23 },
        { "PKT_NPC_Die_EventHistroy", 0x24 },
        { "PKT_UnitAddGold", 0x25 },
        { "PKT_AddUnitPerceptionBubble", 0x26 },
        { "PKT_S2C_MoveCameraToPoint", 0x27 },
        { "PKT_S2C_LineMissileHitList", 0x28 },
        { "PKT_S2C_MuteVolumeCategory", 0x29 },
        { "PKT_ServerTick", 0x2A },
        { "PKT_S2C_StopAnimation", 0x2B },
        { "PKT_AvatarInfo_Server", 0x2C },
        { "PKT_DampenerSwitch", 0x2D },
        { "PKT_World_SendCamera_Server_Acknologment", 0x2E },
        { "PKT_S2C_ModifyDebugCircleRadius", 0x2F },
        { "PKT_World_SendCamera_Server", 0x30 },
        { "PKT_HeroReincarnateAlive", 0x31 },
        { "PKT_NPC_BuffReplace", 0x32 },
        { "PKT_Pause", 0x33 },
        { "PKT_SetFadeOut_Pop", 0x34 },
        { "PKT_ChangeSlotSpellName", 0x35 },
        { "PKT_ChangeSlotSpellIcon", 0x36 },
        { "PKT_ChangeSlotSpellOffsetTarget", 0x37 },
        { "PKT_RemovePerceptionBubble", 0x38 },
        { "PKT_NPC_InstantStop_Attack", 0x39 },
        { "PKT_OnLeaveLocalVisiblityClient", 0x3A },
        { "PKT_S2C_ShowObjectiveText", 0x3B },
        { "PKT_CHAR_SpawnPet", 0x3C },
        { "PKT_FX_Kill", 0x3D },
        { "PKT_NPC_UpgradeSpellReq", 0x3E },
        { "PKT_UseObjectC2S", 0x3F },
        { "PKT_Turret_CreateTurret", 0x40 },
        { "PKT_MissileReplication", 0x41 },
        { "PKT_ResetForSlowLoader", 0x42 },
        { "PKT_S2C_HighlightHUDElement", 0x43 },
        { "PKT_SwapItemAns", 0x44 },
        { "PKT_NPC_LevelUp", 0x45 },
        { "PKT_S2C_MapPing", 0x46 },
        { "PKT_S2C_WriteNavFlags", 0x47 },
        { "PKT_S2C_PlayEmote", 0x48 },
        { "PKT_S2C_Reconnect_Done", 0x49 },
        { "PKT_S2C_OnEventWorld", 0x4A },
        { "PKT_S2C_HeroStats", 0x4B },
        { "PKT_C2S_PlayEmote", 0x4C },
        { "PKT_HeroReincarnate", 0x4D },
        { "PKT_C2S_OnScoreBoardOpened", 0x4E },
        { "PKT_S2C_CreateHero", 0x4F },
        { "PKT_Unused_SPM_AddMemoryListener", 0x50 },
        { "PKT_Unused_SPM_HierarchicalMemoryUpdate", 0x51 },
        { "PKT_S2C_ToggleUIHighlight", 0x52 },
        { "PKT_S2C_FaceDirection", 0x53 },
        { "PKT_OnLeaveVisiblityClient", 0x54 },
        { "PKT_C2S_ClientReady", 0x55 },
        { "PKT_SetItem", 0x56 },
        { "PKT_SynchVersionS2C", 0x57 },
        { "PKT_S2C_HandleTipUpdate", 0x58 },
        { "PKT_C2S_StatsUpdateReq", 0x59 },
        { "PKT_C2S_MapPing", 0x5A },
        { "PKT_S2C_RemoveDebugCircle", 0x5B },
        { "PKT_S2C_CreateUnitHighlight", 0x5C },
        { "PKT_S2C_DestroyClientMissile", 0x5D },
        { "PKT_S2C_LevelUpSpell", 0x5E },
        { "PKT_S2C_StartGame", 0x5F },
        { "PKT_C2S_OnShopOpened", 0x60 },
        { "PKT_NPC_Hero_Die", 0x61 },
        { "PKT_S2C_FadeOutMainSFX", 0x62 },
        { "PKT_UserMessagesStart", 0x63 },
        { "PKT_WaypointGroup", 0x64 },
        { "PKT_S2C_StartSpawn", 0x65 },
        { "PKT_S2C_CreateNeutral", 0x66 },
        { "PKT_WaypointGroupWithSpeed", 0x67 },
        { "PKT_UnitApplyDamage", 0x68 },
        { "PKT_ModifyShield", 0x69 },
        { "PKT_S2C_PopCharacterData", 0x6A },
        { "PKT_NPC_BuffAddGroup", 0x6B },
        { "PKT_S2C_AI_TargetSelection", 0x6C },
        { "PKT_AI_TargetS2C", 0x6D },
        { "PKT_S2C_SetAnimStates", 0x6E },
        { "PKT_S2C_ChainMissileSync", 0x6F },
        { "PKT_C2S_OnTipEvent", 0x70 },
        { "PKT_MissileReplication_ChainMissile", 0x71 },
        { "PKT_BuyItemAns", 0x72 },
        { "PKT_S2C_SetSpellData", 0x73 },
        { "PKT_S2C_PauseAnimation", 0x74 },
        { "PKT_NPC_IssueOrderReq", 0x75 },
        { "PKT_S2C_CameraBehavior", 0x76 },
        { "PKT_S2C_AnimatedBuildingSetCurrentSkin", 0x77 },
        { "PKT_Connected", 0x78 },
        { "PKT_SyncSimTimeFinalS2C", 0x79 },
        { "PKT_Waypoint_Acc", 0x7A },
        { "PKT_AddPosPerceptionBubble", 0x7B },
        { "PKT_S2C_LockCamera", 0x7C },
        { "PKT_S2C_PlayVOAudioEvent", 0x7D },
        { "PKT_AI_Command", 0x7E },
        { "PKT_NPC_BuffRemove2", 0x7F },
        { "PKT_SpawnMinionS2C", 0x80 },
        { "PKT_Unused_ClientCheatDetectionSignal", 0x81 },
        { "PKT_S2C_ToggleFoW", 0x82 },
        { "PKT_S2C_ToolTipVars", 0x83 },
        { "PKT_UnitApplyHeal", 0x84 },
        { "PKT_GlobalCombatMessage", 0x85 },
        { "PKT_World_LockCamera_Server", 0x86 },
        { "PKT_BuyItemReq", 0x87 },
        { "PKT_WaypointListHeroWithSpeed", 0x88 },
        { "PKT_S2C_SetInputLockingFlag", 0x89 },
        { "PKT_CHAR_SetCooldown", 0x8A },
        { "PKT_CHAR_CancelTargetingReticle", 0x8B },
        { "PKT_FX_Create_Group", 0x8C },
        { "PKT_S2C_QueryStatusAns", 0x8D },
        { "PKT_Building_Die", 0x8E },
        { "PKT_Unused_SPM_RemoveListener", 0x8F },
        { "PKT_S2C_HandleQuestUpdate", 0x90 },
        { "PKT_C2S_ClientFinished", 0x91 },
        { "PKT_CHAT", 0x92 },
        { "PKT_Unused_SPM_RemoveMemoryListener", 0x93 },
        { "PKT_C2S_Exit", 0x94 },
        { "PKT_ServerGameSettings", 0x95 },
        { "PKT_S2C_ModifyDebugCircleColor", 0x96 },
        { "PKT_Unused_SPM_AddListener", 0x97 },
        { "PKT_World_SendGameNumber", 0x98 },
        { "PKT_ChangePARColorOverride", 0x99 },
        { "PKT_C2S_ClientConnect_NamedPipe", 0x9A },
        { "PKT_NPC_BuffRemoveGroup", 0x9B },
        { "PKT_Turret_Fire", 0x9C },
        { "PKT_S2C_Ping_Load_Info", 0x9D },
        { "PKT_S2C_ChangeCharacterVoice", 0x9E },
        { "PKT_S2C_ChangeCharacterData", 0x9F },
        { "PKT_S2C_Exit", 0xA0 },
        { "PKT_Unused_SPM_RemoveBBProfileListener", 0xA1 },
        { "PKT_NPC_CastSpellReq", 0xA2 },
        { "PKT_S2C_ToggleInputLockingFlag", 0xA3 },
        { "PKT_C2S_Reconnect", 0xA4 },
        { "PKT_S2C_CreateTurret", 0xA5 },
        { "PKT_NPC_Die", 0xA6 },
        { "PKT_UseItemAns", 0xA7 },
        { "PKT_S2C_ShowAuxiliaryText", 0xA8 },
        { "PKT_PausePacket", 0xA9 },
        { "PKT_S2C_HideObjectiveText", 0xAA },
        { "PKT_OnEvent", 0xAB },
        { "PKT_C2S_TeamSurrenderVote", 0xAC },
        { "PKT_S2C_TeamSurrenderStatus", 0xAD },
        { "PKT_Unused_SPM_AddBBProfileListener", 0xAE },
        { "PKT_S2C_HideAuxiliaryText", 0xAF },
        { "PKT_OnReplication_Acc", 0xB0 },
        { "PKT_OnDisconnected", 0xB1 },
        { "PKT_S2C_SetGreyscaleEnabledWhenDead", 0xB2 },
        { "PKT_S2C_AI_State", 0xB3 },
        { "PKT_S2C_SetFoWStatus", 0xB4 },
        { "PKT_OnEnterLocalVisiblityClient", 0xB5 },
        { "PKT_S2C_HighlightShopElement", 0xB6 },
        { "PKT_SendSelectedObjID", 0xB7 },
        { "PKT_S2C_PlayAnimation", 0xB8 },
        { "PKT_S2C_RefreshAuxiliaryText", 0xB9 },
        { "PKT_SetFadeOut_Push", 0xBA },
        { "PKT_S2C_OpenTutorialPopup", 0xBB },
        { "PKT_S2C_RemoveUnitHighlight", 0xBC },
        { "PKT_NPC_CastSpellAns", 0xBD },
        { "PKT_Unused_SPM_HierarchicalBBProfileUpdate", 0xBE },
        { "PKT_NPC_BuffAdd2", 0xBF },
        { "PKT_S2C_OpenAFKWarningMessage", 0xC0 },
        { "PKT_WaypointList", 0xC1 },
        { "PKT_OnEnterVisiblityClient", 0xC2 },
        { "PKT_S2C_AddDebugCircle", 0xC3 },
        { "PKT_S2C_DisableHUDForEndOfGame", 0xC4 },
        { "PKT_SynchVersionC2S", 0xC5 },
        { "PKT_C2S_CharSelected", 0xC6 },
        { "PKT_NPC_BuffUpdateCountGroup", 0xC7 },
        { "PKT_AI_TargetHeroS2C", 0xC8 },
        { "PKT_SynchSimTimeS2C", 0xC9 },
        { "PKT_SyncMissionStartTimeS2C", 0xCA },
        { "PKT_S2C_Neutral_Camp_Empty", 0xCB },
        { "PKT_OnReplication", 0xCC },
        { "PKT_S2C_EndOfGameEvent", 0xCD },
        { "PKT_S2C_EndGame", 0xCE },
        { "PKT_Unused_Undefined", 0xCF },
        { "PKT_Unused_SPM_SamplingProfilerUpdate", 0xD0 },
        { "PKT_S2C_PopAllCharacterData", 0xD1 },
        { "PKT_S2C_TeamSurrenderVote", 0xD2 },
        { "PKT_S2C_HandleUIHighlight", 0xD3 },
        { "PKT_S2C_FadeMinions", 0xD4 },
        { "PKT_C2S_OnTutorialPopupClosed", 0xD5 },
        { "PKT_C2S_OnQuestEvent", 0xD6 },
        { "PKT_S2C_ShowHealthBar", 0xD7 },
        { "PKT_SpawnBotS2C", 0xD8 },
        { "PKT_SpawnLevelPropS2C", 0xD9 },
        { "PKT_UpdateLevelPropS2C", 0xDA },
        { "PKT_AttachFlexParticleS2C", 0xDB },
        { "PKT_S2C_HandleCapturePointUpdate", 0xDC },
        { "PKT_S2C_HandleGameScore", 0xDD },
        { "PKT_S2C_HandleRespawnPointUpdate", 0xDE },
        { "PKT_C2S_OnRespawnPointEvent", 0xDF },
        { "PKT_S2C_UnitChangeTeam", 0xE0 },
        { "PKT_S2C_UnitSetMinimapIcon", 0xE1 },
        { "PKT_S2C_IncrementPlayerScore", 0xE2 },
        { "PKT_S2C_IncrementPlayerStat", 0xE3 },
        { "PKT_S2C_ColorRemapFX", 0xE4 },
        { "PKT_S2C_MusicCueCommand", 0xE5 },
        { "PKT_Unused_S2C_AntiBot", 0xE6 },
        { "PKT_Unused_S2C_AntiBotWriteLog", 0xE7 },
        { "PKT_Unused_S2C_AntiBotKickOut", 0xE8 },
        { "PKT_Unused_S2C_AntiBotBanPlayer", 0xE9 },
        { "PKT_Unused_S2C_AntiBotTrojan", 0xEA },
        { "PKT_Unused_S2C_AntiBotCloseClient", 0xEB },
        { "PKT_Unused_C2S_AntiBotDP", 0xEC },
        { "PKT_Unused_ED", 0xED },
        { "PKT_S2C_OnEnterTeamVisiblity", 0xEE },
        { "PKT_S2C_OnLeaveTeamVisiblity", 0xEF },
        { "PKT_S2C_FX_OnEnterTeamVisiblity", 0xF0 },
        { "PKT_S2C_FX_OnLeaveTeamVisiblity", 0xF1 },
        { "PKT_ReplayOnly_GoldEarned", 0xF2 },
        { "PKT_ExtendedPacket", 0xFE },
        { "PKT_Batch", 0xFF },
    };
    return info;
}

void ProtoVer::read(Data_in& io, PKT_S2C_CreateHero& value) const {
    io.num<uint32_t>(value.fromID);
    io.num<uint32_t>(value.netObjID);
    io.num<uint32_t>(value.playerUID);
    io.num<uint8_t>(value.netNodeID);
    io.num<uint8_t>(value.skillLevel);
    io.num<bool>(value.teamIsOrder);
    io.num<bool>(value.isBot);
    io.num<uint8_t>(value.botRank);
    io.num<uint8_t>(value.spawnPosIndex);
    io.num<int32_t>(value.skinID);
    io.fstr(value.Name, 128);
    io.fstr(value.Skin, 40);
}
void ProtoVer::write(Data_out& io, PKT_S2C_CreateHero const& value) const {
    io.num<uint32_t>(value.fromID);
    io.num<uint32_t>(value.netObjID);
    io.num<uint32_t>(value.playerUID);
    io.num<uint8_t>(value.netNodeID);
    io.num<uint8_t>(value.skillLevel);
    io.num<bool>(value.teamIsOrder);
    io.num<bool>(value.isBot);
    io.num<uint8_t>(value.botRank);
    io.num<uint8_t>(value.spawnPosIndex);
    io.num<int32_t>(value.skinID);
    io.fstr(value.Name, 128);
    io.fstr(value.Skin, 40);
}
