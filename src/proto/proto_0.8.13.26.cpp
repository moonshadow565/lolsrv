#include "proto_0.8.13.26.hpp"

using ProtoVer = PROTO_VER(0.8.13.26);

std::string_view ProtoVer::name() const { return "0.8.13.26"; }

Span<ProtoNameID const> ProtoVer::egp_array() const {
    static ProtoNameID const info[] = {
        { "EGP_RequestJoinTeam", 0x64 },
        { "EGP_RequestReskin", 0x65 },
        { "EGP_RequestRename", 0x66 },
        { "EGP_TeamRosterUpdate", 0x67 },
        { "EGP_Chat", 0x68 },
        { "EGP_sendToServer", 0x69 },
        { "EGP_broadcastToClients", 0x6A },
    };
    return info;
}

Span<ProtoNameID const> ProtoVer::pkt_array() const {
    static ProtoNameID const info[] = {
        { "PKT_Dummy", 0x0 },
        { "PKT_C2S_ClientConnect_NamedPipe", 0x1 },
        { "PKT_CHAT", 0x2 },
        { "PKT_C2S_QueryStatusReq", 0x03 },
        { "PKT_S2C_QueryStatusAns", 0x04 },
        { "PKT_S2C_StartSpawn", 0x05 },
        { "PKT_S2C_CreateHero", 0x06 },
        { "PKT_S2C_CreateNeutral", 0x07 },
        { "PKT_S2C_CreateTurret", 0x08 },
        { "PKT_S2C_PlayAnimation", 0x9 },
        { "PKT_C2S_PlayEmote", 0xA },
        { "PKT_S2C_PlayEmote", 0xB },
        { "PKT_S2C_EndSpawn", 0x0C },
        { "PKT_S2C_StartGame", 0x0D },
        { "PKT_S2C_EndGame", 0xE },
        { "PKT_C2S_CharSelected", 0x0F },
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
        { "PKT_NPC_CastSpellReq", 0x23 },
        { "PKT_NPC_CastSpellAns", 0x24 },
        { "PKT_NPC_BuffAdd2", 0x25 },
        { "PKT_NPC_BuffRenew", 0x26 },
        { "PKT_NPC_BuffRemove2", 0x27 },
        { "PKT_NPC_SetAutocast", 0x28 },
        { "PKT_BuyItemReq", 0x29 },
        { "PKT_BuyItemAns", 0x2A },
        { "PKT_RemoveItemReq", 0x2B },
        { "PKT_RemoveItemAns", 0x2C },
        { "PKT_SwapItemReq", 0x2D },
        { "PKT_SwapItemAns", 0x2E },
        { "PKT_NPC_LevelUp", 0x2F },
        { "PKT_NPC_InstantStop_Attack", 0x30 },
        { "PKT_NPC_UpdateLocalVars32_1", 0x31 },
        { "PKT_NPC_UpdateLocalVars32_2", 0x32 },
        { "PKT_NPC_UpdateMapVars32", 0x33 },
        { "PKT_NPC_UpdateOnVisibleVars32", 0x34 },
        { "PKT_Barrack_SpawnUnit", 0x35 },
        { "PKT_Turret_Fire", 0x36 },
        { "PKT_Turret_CreateTurret", 0x37 },
        { "pkt32", 0x38 },
        { "PKT_Basic_Attack", 0x39 },
        { "PKT_Basic_Attack_Pos", 0x3A },
        { "PKT_OnEnterVisiblityClient", 0x3B },
        { "PKT_OnLeaveVisiblityClient", 0x3C },
        { "PKT_OnEnterLocalVisiblityClient", 0x3D },
        { "PKT_OnLeaveLocalVisiblityClient", 0x3E },
        { "PKT_World_SendCamera_Server", 0x3F },
        { "PKT_World_LockCamera_Server", 0x40 },
        { "PKT_SendSelectedObjID", 0x41 },
        { "PKT_UnitApplyHeal", 0x42 },
        { "PKT_MissileReplication", 0x43 },
        { "PKT_ServerTick", 0x44 },
        { "PKT_DampenerSwitch", 0x45 },
        { "PKT_GlobalCombatMessage", 0x46 },
        { "PKT_SynchVersionC2S", 0x47 },
        { "PKT_SynchVersionS2C", 0x48 },
        { "PKT_AI_TargetS2C", 0x49 },
        { "PKT_HeroReincarnateAlive", 0x4A },
        { "PKT_HeroReincarnate", 0x4B },
        { "PKT_Building_Die", 0x4C },
        { "PKT_SynchSimTimeS2C", 0x4D },
        { "PKT_SynchSimTimeC2S", 0x4E },
        { "PKT_SyncSimTimeFinalS2C", 0x4F },
        { "PKT_WaypointList", 0x50 },
        { "PKT_WaypointListHeroWithSpeed", 0x51 },
        { "PKT_ServerGameSettings", 0x52 },
        { "PKT_NPC_BuffUpdateCount", 0x53 },
        { "PKT_C2S_PlayEmoticon", 0x54 },
        { "PKT_S2C_PlayEmoticon", 0x55 },
        { "PKT_AvatarInfo_Server", 0x56 },
        { "PKT_RemovePerceptionBubble", 0x57 },
        { "PKT_AddUnitPerceptionBubble", 0x58 },
        { "PKT_AddPosPerceptionBubble", 0x59 },
        { "PKT_SpawnMinionS2C", 0x5A },
        { "PKT_S2C_StopAnimation", 0x5B },
        { "PKT_UpdateGoldRedirectTarget", 0x5C },
        { "PKT_S2C_ChangeCharacterData", 0x5D },
        { "PKT_S2C_PopCharacterData", 0x5E },
        { "PKT_S2C_PopAllCharacterData", 0x5F },
        { "PKT_S2C_FaceDirection", 0x60 },
        { "PKT_S2C_CameraBehavior", 0x61 },
        { "PKT_SPM_AddListener", 0x62 },
        { "PKT_SPM_RemoveListener", 0x63 },
        { "PKT_SPM_HierarchicalProfilerUpdate", 0x64 },
        { "PKT_SPM_SamplingProfilerUpdate", 0x65 },
        { "PKT_SPM_HierarchicalMemoryUpdate", 0x66 },
        { "PKT_SPM_AddMemoryListener", 0x67 },
        { "PKT_SPM_RemoveMemoryListener", 0x68 },
        { "PKT_S2C_DestroyClientMissile", 0x69 },
        { "PKT_S2C_ChainMissileSync", 0x6A },
        { "PKT_MissileReplication_ChainMissile", 0x6B },
        { "PKT_S2C_AI_TargetSelection", 0x6C },
        { "PKT_S2C_AI_State", 0x6D },
        { "PKT_OnEvent", 0x6E },
        { "PKT_OnDisconnected", 0x6F },
        { "PKT_World_SendCamera_Server_Acknologment", 0x70 },
        { "PKT_World_SendGameNumber", 0x71 },
        { "PKT_Extended", 0x72 },
    };
    return info;
}

void ProtoVer::read(Data_in& in, EGP_ID& value) const {
    in.read_num<uint8_t>(value);
    in.read_pad(3);
}
void ProtoVer::write(Data_out& out, EGP_ID const& value) const {
    out.write_num<uint8_t>(value);
    out.write_pad(3);
}

void ProtoVer::read(Data_in& in, PKT_ID& value) const {
    in.read_num<uint16_t>(value);
    uint16_t other = {};
    in.read_num<uint16_t>(other);
    if (value == (PKT_ID)0x72) {
        value = (PKT_ID)other;
    }
}
void ProtoVer::write(Data_out& out, PKT_ID const& value) const {
    out.write_num<uint16_t>(value);
    out.write_num<uint16_t>(value);
}

void ProtoVer::read(Data_in& in, EGP_RequestJoinTeam& value) const {
    in.read_num<int32_t>(value.Id_Player);
    in.read_num<uint32_t>(value.team);
}
void ProtoVer::write(Data_out& out, EGP_RequestJoinTeam const& value) const {
    out.write_num<int32_t>(value.Id_Player);
    out.write_num<uint32_t>(value.team);
}

void ProtoVer::read(Data_in& in, EGP_RequestRename& value) const {
    in.read_pad(4);
    in.read_num<int64_t>(value.Id_Player);
    in.read_num<int32_t>(value.skinID);
    in.read_szstr(value.buffer);
}
void ProtoVer::write(Data_out& out, EGP_RequestRename const& value) const {
    out.write_pad(4);
    out.write_num<int64_t>(value.Id_Player);
    out.write_num<int32_t>(value.skinID);
    out.write_szstr(value.buffer);
}

void ProtoVer::read(Data_in& in, EGP_RequestReskin& value) const {
    in.read_pad(4);
    in.read_num<int64_t>(value.Id_Player);
    in.read_num<int32_t>(value.skinID);
    in.read_szstr(value.buffer);
}
void ProtoVer::write(Data_out& out, EGP_RequestReskin const& value) const {
    out.write_pad(4);
    out.write_num<int64_t>(value.Id_Player);
    out.write_num<int32_t>(value.skinID);
    out.write_szstr(value.buffer);
}

void ProtoVer::read(Data_in& in, EGP_Chat& value) const {
    in.read_zstr(value.message);
}
void ProtoVer::write(Data_out& out, EGP_Chat const& value) const {
    out.write_zstr(value.message);
}

void ProtoVer::read(Data_in& in, EGP_TeamRosterUpdate& value) const {
    in.read_num<uint32_t>(value.teamsize_order);
    in.read_num<uint32_t>(value.teamsize_chaos);
    in.read_pad(4);
    in.read_num_array<int64_t>(value.orderMembers);
    in.read_num_array<int64_t>(value.chaosMembers);
    in.read_num<uint32_t>(value.current_teamsize_order);
    in.read_num<uint32_t>(value.current_teamsize_chaos);
}
void ProtoVer::write(Data_out& out, EGP_TeamRosterUpdate const& value) const {
    out.write_num<uint32_t>(value.teamsize_order);
    out.write_num<uint32_t>(value.teamsize_chaos);
    out.write_pad(4);
    out.write_num_array<int64_t>(value.orderMembers);
    out.write_num_array<int64_t>(value.chaosMembers);
    out.write_num<uint32_t>(value.current_teamsize_order);
    out.write_num<uint32_t>(value.current_teamsize_chaos);
}

void ProtoVer::read(Data_in& in, CommonBasicAttack& value) const {
    in.read_num<uint32_t>(value.targetNetId);
    in.read_num<float>(value.extraTime);
    in.read_num<uint32_t>(value.missileNextID);
    in.read_num<uint8_t>(value.attackSlot);
}
void ProtoVer::write(Data_out& out, CommonBasicAttack const& value) const {
    out.write_num<uint32_t>(value.targetNetId);
    out.write_num<float>(value.extraTime);
    out.write_num<uint32_t>(value.missileNextID);
    out.write_num<uint8_t>(value.attackSlot);
}

void ProtoVer::read(Data_in& in, ConnectionInfo& value) const {
    in.read_num<int32_t>(value.mClientID);
    in.read_num<int64_t>(value.mPlayerID);
    in.read_num<float>(value.mPercentage);
    in.read_num<float>(value.mETA);
    in.read_bit<uint32_t>(
                field<int32_t, 16>(value.mCount),
                field<uint32_t, 15>(value.mPing),
                field<uint32_t, 1>(value.mPad));
    in.read_num<uint8_t>(value.mReady);
    in.read_zstr(value.mState);
}
void ProtoVer::write(Data_out& out, ConnectionInfo const& value) const {
    out.write_num<int32_t>(value.mClientID);
    out.write_num<int64_t>(value.mPlayerID);
    out.write_num<float>(value.mPercentage);
    out.write_num<float>(value.mETA);
    out.write_bit<uint32_t>(
                field<int32_t, 16>(value.mCount),
                field<uint32_t, 15>(value.mPing),
                field<uint32_t, 1>(value.mPad));
    out.write_num<uint8_t>(value.mReady);
    out.write_zstr(value.mState);
}

void ProtoVer::read(Data_in& in, PlayerLiteInfo& value) const {
    in.read_num<int64_t>(value.ID);
    in.read_num<uint16_t>(value.summonorLevel);
    in.read_num<uint32_t>(value.summonorSpell1);
    in.read_num<uint32_t>(value.summonorSpell2);
}
void ProtoVer::write(Data_out& out, PlayerLiteInfo const& value) const {
    out.write_num<int64_t>(value.ID);
    out.write_num<uint16_t>(value.summonorLevel);
    out.write_num<uint32_t>(value.summonorSpell1);
    out.write_num<uint32_t>(value.summonorSpell2);
}

void ProtoVer::read(Data_in& in, PKT_Basic_Attack& value) const {
    in.read_num<uint32_t>(value.fromID);
    read(in, value.data);
}
void ProtoVer::write(Data_out& out, PKT_Basic_Attack const& value) const {
    out.write_num<uint32_t>(value.fromID);
    write(out, value.data);
}

void ProtoVer::read(Data_in& in, PKT_Basic_Attack_Pos& value) const {
    in.read_num<uint32_t>(value.fromID);
    read(in, value.data);
    in.read_num<float>(value.pos.x);
    in.read_pad(4);
    in.read_num<float>(value.pos.y);
}
void ProtoVer::write(Data_out& out, PKT_Basic_Attack_Pos const& value) const {
    out.write_num<uint32_t>(value.fromID);
    write(out, value.data);
    out.write_num<float>(value.pos.x);
    out.write_pad(4);
    out.write_num<float>(value.pos.y);
}

void ProtoVer::read(Data_in& in, PKT_BuyItemAns& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint8_t>(value.slot);
    in.read_num<uint32_t>(value.itemID);
    in.read_num<uint8_t>(value.itemsInSlot);
}
void ProtoVer::write(Data_out& out, PKT_BuyItemAns const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint8_t>(value.slot);
    out.write_num<uint32_t>(value.itemID);
    out.write_num<uint8_t>(value.itemsInSlot);
}

void ProtoVer::read(Data_in& in, PKT_BuyItemReq& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint32_t>(value.itemID);
}
void ProtoVer::write(Data_out& out, PKT_BuyItemReq const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint32_t>(value.itemID);
}

void ProtoVer::read(Data_in& in, PKT_C2S_CharSelected& value) const {
    in.read_num<uint32_t>(value.fromID);
}
void ProtoVer::write(Data_out& out, PKT_C2S_CharSelected const& value) const {
    out.write_num<uint32_t>(value.fromID);
}

void ProtoVer::read(Data_in& in, PKT_C2S_ClientReady& value) const {
    in.read_num<uint32_t>(value.fromID);
}
void ProtoVer::write(Data_out& out, PKT_C2S_ClientReady const& value) const {
    out.write_num<uint32_t>(value.fromID);
}

void ProtoVer::read(Data_in& in, PKT_C2S_MapPing& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_point3d(value.pos);
    in.read_num<uint32_t>(value.target);
}
void ProtoVer::write(Data_out& out, PKT_C2S_MapPing const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_point3d(value.pos);
    out.write_num<uint32_t>(value.target);
}

void ProtoVer::read(Data_in& in, PKT_C2S_Ping_Load_Info& value) const {
    in.read_num<uint32_t>(value.fromID);
    read(in, value.mConnectionInfo);
}
void ProtoVer::write(Data_out& out, PKT_C2S_Ping_Load_Info const& value) const {
    out.write_num<uint32_t>(value.fromID);
    write(out, value.mConnectionInfo);
}

void ProtoVer::read(Data_in& in, PKT_C2S_PlayEmote& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint32_t>(value.mEmoteId);
}
void ProtoVer::write(Data_out& out, PKT_C2S_PlayEmote const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint32_t>(value.mEmoteId);
}

void ProtoVer::read(Data_in& in, PKT_C2S_QueryStatusReq& value) const {
    in.read_num<uint32_t>(value.fromID);
}
void ProtoVer::write(Data_out& out, PKT_C2S_QueryStatusReq const& value) const {
    out.write_num<uint32_t>(value.fromID);
}

void ProtoVer::read(Data_in& in, PKT_C2S_Reconnect& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<bool>(value.isFullReconnect);
}
void ProtoVer::write(Data_out& out, PKT_C2S_Reconnect const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<bool>(value.isFullReconnect);
}

void ProtoVer::read(Data_in& in, PKT_NPC_Die& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint32_t>(value.killerNetID);
    in.read_num<uint8_t>(value.damageType);
    in.read_num<uint8_t>(value.mSpellSourceType);
    in.read_num<float>(value.DeathDuration);
}
void ProtoVer::write(Data_out& out, PKT_NPC_Die const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint32_t>(value.killerNetID);
    out.write_num<uint8_t>(value.damageType);
    out.write_num<uint8_t>(value.mSpellSourceType);
    out.write_num<float>(value.DeathDuration);
}

void ProtoVer::read(Data_in& in, PKT_NPC_IssueOrderReq& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint8_t>(value.order);
    in.read_point3d(value.pos);
    in.read_num<uint32_t>(value.targetNetID);
}
void ProtoVer::write(Data_out& out, PKT_NPC_IssueOrderReq const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint8_t>(value.order);
    out.write_point3d(value.pos);
    out.write_num<uint32_t>(value.targetNetID);
}

void ProtoVer::read(Data_in& in, PKT_NPC_LevelUp& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint8_t>(value.mLevel);
    in.read_num<uint8_t>(value.mPoints);
}
void ProtoVer::write(Data_out& out, PKT_NPC_LevelUp const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint8_t>(value.mLevel);
    out.write_num<uint8_t>(value.mPoints);
}

void ProtoVer::read(Data_in& in, PKT_NPC_UpgradeSpellAns& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint8_t>(value.slot);
    in.read_num<uint8_t>(value.spellLevel);
    in.read_num<uint8_t>(value.spellTrainingPoints);
}
void ProtoVer::write(Data_out& out, PKT_NPC_UpgradeSpellAns const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint8_t>(value.slot);
    out.write_num<uint8_t>(value.spellLevel);
    out.write_num<uint8_t>(value.spellTrainingPoints);
}

void ProtoVer::read(Data_in& in, PKT_NPC_UpgradeSpellReq& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint8_t>(value.slot);
}
void ProtoVer::write(Data_out& out, PKT_NPC_UpgradeSpellReq const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint8_t>(value.slot);
}

void ProtoVer::read(Data_in& in, PKT_OnEnterVisiblityClient& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_OnEnterVisiblityClient const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint8_t>(value.items.size());
    for (auto const& elem: value.items) {
        out.write_num<uint8_t>(elem.slot);
        out.write_num<uint8_t>(elem.itemsInSlot);
        out.write_num<uint8_t>(elem.spellCharges);
        out.write_num<uint32_t>(elem.itemID);
    }
    if (value.lookat) {
        out.write_num<uint8_t>(1);
        out.write_point3d(*value.lookat);
    } else {
        out.write_num<uint8_t>(0);
    }
    if (value.position) {
        out.write_num<uint8_t>(3);
        out.write_num<uint32_t>(value.syncId);
        out.write_point2d(*value.position);
        out.write_point2d(*value.position);
    }
}

void ProtoVer::read(Data_in& in, PKT_RemoveItemAns& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint8_t>(value.slot);
    in.read_num<uint8_t>(value.itemsInSlot);
}
void ProtoVer::write(Data_out& out, PKT_RemoveItemAns const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint8_t>(value.slot);
    out.write_num<uint8_t>(value.itemsInSlot);
}

void ProtoVer::read(Data_in& in, PKT_RemoveItemReq& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint8_t>(value.slot);
    in.read_num<bool>(value.bSell);
}
void ProtoVer::write(Data_out& out, PKT_RemoveItemReq const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint8_t>(value.slot);
    out.write_num<bool>(value.bSell);
}

void ProtoVer::read(Data_in& in, PKT_S2C_ChangeCharacterData& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint32_t>(value.id);
    in.read_fstr(value.skinName, 64);
}
void ProtoVer::write(Data_out& out, PKT_S2C_ChangeCharacterData const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint32_t>(value.id);
    out.write_fstr(value.skinName, 64);
}

void ProtoVer::read(Data_in& in, PKT_S2C_CreateHero& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint32_t>(value.netObjID);
    in.read_num<uint8_t>(value.netNodeID);
    in.read_num<uint32_t>(value.playerUID);
    in.read_num<bool>(value.teamIsOrder);
    in.read_num<bool>(value.isBot);
    in.read_fstr(value.Name, 40);
    in.read_fstr(value.Skin, 40);
}
void ProtoVer::write(Data_out& out, PKT_S2C_CreateHero const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint32_t>(value.netObjID);
    out.write_num<uint8_t>(value.netNodeID);
    out.write_num<uint32_t>(value.playerUID);
    out.write_num<bool>(value.teamIsOrder);
    out.write_num<bool>(value.isBot);
    out.write_fstr(value.Name, 40);
    out.write_fstr(value.Skin, 40);
}

void ProtoVer::read(Data_in& in, PKT_S2C_CreateTurret& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint32_t>(value.netObjID);
    in.read_num<uint8_t>(value.netNodeID);
    in.read_fstr(value.Name, 64);
}
void ProtoVer::write(Data_out& out, PKT_S2C_CreateTurret const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint32_t>(value.netObjID);
    out.write_num<uint8_t>(value.netNodeID);
    out.write_fstr(value.Name, 64);
}

void ProtoVer::read(Data_in& in, PKT_S2C_FaceDirection& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_point3d(value.direction);
}
void ProtoVer::write(Data_out& out, PKT_S2C_FaceDirection const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_point3d(value.direction);
}

void ProtoVer::read(Data_in& in, PKT_S2C_EndSpawn& value) const {
    in.read_num<uint32_t>(value.fromID);
}
void ProtoVer::write(Data_out& out, PKT_S2C_EndSpawn const& value) const {
    out.write_num<uint32_t>(value.fromID);
}

void ProtoVer::read(Data_in& in, PKT_S2C_Ping_Load_Info& value) const {
    in.read_num<uint32_t>(value.fromID);
    read(in, value.mConnectionInfo);
}
void ProtoVer::write(Data_out& out, PKT_S2C_Ping_Load_Info const& value) const {
    out.write_num<uint32_t>(value.fromID);
    write(out, value.mConnectionInfo);
}

void ProtoVer::read(Data_in& in, PKT_S2C_PlayAnimation& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint32_t>(value.flags);
    in.read_num<float>(value.scaleTime);
    in.read_zstr(value.animationName);
}
void ProtoVer::write(Data_out& out, PKT_S2C_PlayAnimation const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint32_t>(value.flags);
    out.write_num<float>(value.scaleTime);
    out.write_zstr(value.animationName);
}

void ProtoVer::read(Data_in& in, PKT_S2C_PlayEmote& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint32_t>(value.mEmoteId);
}
void ProtoVer::write(Data_out& out, PKT_S2C_PlayEmote const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint32_t>(value.mEmoteId);
}

void ProtoVer::read(Data_in& in, PKT_S2C_MapPing& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_point3d(value.pos);
    in.read_num<uint32_t>(value.target);
    in.read_num<uint32_t>(value.src);
}
void ProtoVer::write(Data_out& out, PKT_S2C_MapPing const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_point3d(value.pos);
    out.write_num<uint32_t>(value.target);
    out.write_num<uint32_t>(value.src);
}

void ProtoVer::read(Data_in& in, PKT_S2C_QueryStatusAns& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<bool>(value.ok);
}
void ProtoVer::write(Data_out& out, PKT_S2C_QueryStatusAns const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<bool>(value.ok);
}

void ProtoVer::read(Data_in& in, PKT_S2C_Reconnect& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<int32_t>(value.cid);
}
void ProtoVer::write(Data_out& out, PKT_S2C_Reconnect const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<int32_t>(value.cid);
}

void ProtoVer::read(Data_in& in, PKT_S2C_StartGame& value) const {
    in.read_num<uint32_t>(value.fromID);
}
void ProtoVer::write(Data_out& out, PKT_S2C_StartGame const& value) const {
    out.write_num<uint32_t>(value.fromID);
}

void ProtoVer::read(Data_in& in, PKT_SwapItemAns& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint8_t>(value.source);
    in.read_num<uint8_t>(value.dest);
}
void ProtoVer::write(Data_out& out, PKT_SwapItemAns const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint8_t>(value.source);
    out.write_num<uint8_t>(value.dest);
}

void ProtoVer::read(Data_in& in, PKT_SwapItemReq& value) const {
    in.read_num<uint32_t>(value.fromID);
}
void ProtoVer::write(Data_out& out, PKT_SwapItemReq const& value) const {
    out.write_num<uint32_t>(value.fromID);
}

void ProtoVer::read(Data_in& in, PKT_S2C_StartSpawn& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint8_t>(value.numBotsOrder);
    in.read_num<uint8_t>(value.numBotsChaos);
}
void ProtoVer::write(Data_out& out, PKT_S2C_StartSpawn const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint8_t>(value.numBotsOrder);
    out.write_num<uint8_t>(value.numBotsChaos);
}

void ProtoVer::read(Data_in& in, PKT_SynchVersionC2S& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<float>(value.mTime_LastClient);
    in.read_num<uint32_t>(value.mClientNetID);
    in.read_fstr(value.mVersionString, 256);
}
void ProtoVer::write(Data_out& out, PKT_SynchVersionC2S const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<float>(value.mTime_LastClient);
    out.write_num<uint32_t>(value.mClientNetID);
    out.write_fstr(value.mVersionString, 256);
}

void ProtoVer::read(Data_in& in, PKT_SynchVersionS2C& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<bool>(value.mIsVersionOk);
    in.read_num<int32_t>(value.mMapToLoad);
    for(auto& elem: value.playerInfo) {
        read(in, elem);
    }
    in.read_fstr(value.mVersionString, 256);
}
void ProtoVer::write(Data_out& out, PKT_SynchVersionS2C const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<bool>(value.mIsVersionOk);
    out.write_num<int32_t>(value.mMapToLoad);
    for(auto const& elem: value.playerInfo) {
        write(out, elem);
    }
    out.write_fstr(value.mVersionString, 256);
}

void ProtoVer::read(Data_in& in, PKT_WaypointList& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint32_t>(value.syncID);
    value.list.clear();
    in.read_until_end([&] {
        r3dPoint2D elem = {};
        in.read_point2d(elem);
        value.list.push_back(elem);
    });
}
void ProtoVer::write(Data_out& out, PKT_WaypointList const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint32_t>(value.syncID);
    for(auto const& elem: value.list) {
        out.write_point2d(elem);
    }
}

void ProtoVer::read(Data_in& in, PKT_World_LockCamera_Server& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<bool>(value.lockCamera);
    in.read_num<int32_t>(value.clientID);
}
void ProtoVer::write(Data_out& out, PKT_World_LockCamera_Server const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<bool>(value.lockCamera);
    out.write_num<int32_t>(value.clientID);
}

void ProtoVer::read(Data_in& in, PKT_World_SendCamera_Server& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<int8_t>(value.syncID);
}
void ProtoVer::write(Data_out& out, PKT_World_SendCamera_Server const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_point3d(value.cameraPos);
    out.write_point3d(value.cameraDir);
    out.write_num<int32_t>(value.clientID);
    out.write_num<int8_t>(value.syncID);
}

void ProtoVer::read(Data_in& in, PKT_World_SendCamera_Server_Acknologment& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<int8_t>(value.syncID);
}
void ProtoVer::write(Data_out& out, PKT_World_SendCamera_Server_Acknologment const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<int8_t>(value.syncID);
}


/*
TODO Upgrade:
    PKT_NPC_Die,
    PKT_RemoveItemReq,
    PKT_S2C_ChangeCharacterData,
    PKT_S2C_ToggleFoW,
    CommonBasicAttack,
    PKT_Basic_Attack_Pos,
    PKT_C2S_MapPing,
    PKT_S2C_MapPing,
    PKT_World_SendCamera_Server,
*/
