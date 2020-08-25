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
        { "PKT_C2S_QueryStatusReq", 0x03 },
        { "PKT_S2C_QueryStatusAns", 0x04 },
        { "PKT_S2C_StartSpawn", 0x05 },
        { "PKT_S2C_CreateHero", 0x06 },
        { "PKT_S2C_CreateNeutral", 0x07 },
        { "PKT_S2C_CreateTurret", 0x08 },
        { "PKT_S2C_EndSpawn", 0x0C },
        { "PKT_S2C_StartGame", 0x0D },
        { "PKT_EndGame", 0x0E },
        { "PKT_C2S_CharSelected", 0x0F },
        { "PKT_C2S_ClientReady", 0x10 },
        { "PKT_SynchVersionS2C", 0x48 },
        { "PKT_SpawnMinionS2C", 0x5A },
        { "PKT_World_SendGameNumber", 0x71 },
        { "PKT_NPC_IssueOrderReq", 0x14 },
        { "PKT_WaypointList", 80 },
        { "PKT_S2C_FaceDirection", 96 },
        { "PKT_SynchVersionC2S", 0x47 },
        { "PKT_OnEnterVisiblityClient", 59 },
        { "PKT_C2S_Ping_Load_Info", 0x56 },
        { "PKT_S2C_Ping_Load_Info", 0x57 },
        { "PKT_S2C_Reconnect", 0x40 + 1 },
        { "PKT_C2S_Reconnect", 0x40 },
        { "PKT_Extended", 0x72 },
    };
    return info;
}

void ProtoVer::read(Data_in& in, EGP_ID& value) const {
    in.read_num<uint8_t>(value);
}
void ProtoVer::write(Data_out& out, EGP_ID const& value) const {
    out.write_num<uint8_t>(value);
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
    in.read_pad<3>();
    in.read_num<int32_t>(value.Id_Player);
    in.read_num<uint32_t>(value.team);
}
void ProtoVer::write(Data_out& out, EGP_RequestJoinTeam const& value) const {
    out.write_pad<3>();
    out.write_num<int32_t>(value.Id_Player);
    out.write_num<uint32_t>(value.team);
}

void ProtoVer::read(Data_in& in, EGP_RequestRename& value) const {
    in.read_pad<7>();
    in.read_num<int64_t>(value.Id_Player);
    in.read_num<int32_t>(value.skinID);
    in.read_szstr<uint32_t>(value.buffer);
}
void ProtoVer::write(Data_out& out, EGP_RequestRename const& value) const {
    out.write_pad<7>();
    out.write_num<int64_t>(value.Id_Player);
    out.write_num<int32_t>(value.skinID);
    out.write_szstr<uint32_t>(value.buffer);
}

void ProtoVer::read(Data_in& in, EGP_RequestReskin& value) const {
    in.read_pad<7>();
    in.read_num<int64_t>(value.Id_Player);
    in.read_num<int32_t>(value.skinID);
    in.read_szstr<uint32_t>(value.buffer);
}
void ProtoVer::write(Data_out& out, EGP_RequestReskin const& value) const {
    out.write_pad<7>();
    out.write_num<int64_t>(value.Id_Player);
    out.write_num<int32_t>(value.skinID);
    out.write_szstr<uint32_t>(value.buffer);
}

void ProtoVer::read(Data_in& in, EGP_TeamRosterUpdate& value) const {
    in.read_pad<3>();
    in.read_num<uint32_t>(value.teamsize_order);
    in.read_num<uint32_t>(value.teamsize_chaos);
    in.read_num_array<int64_t>(value.orderMembers);
    in.read_num_array<int64_t>(value.chaosMembers);
    in.read_num<uint32_t>(value.current_teamsize_order);
    in.read_num<uint32_t>(value.current_teamsize_chaos);
}
void ProtoVer::write(Data_out& out, EGP_TeamRosterUpdate const& value) const {
    out.write_pad<3>();
    out.write_num<uint32_t>(value.teamsize_order);
    out.write_num<uint32_t>(value.teamsize_chaos);
    out.write_pad<4>();
    out.write_num_array<int64_t>(value.orderMembers);
    out.write_num_array<int64_t>(value.chaosMembers);
    out.write_num<uint32_t>(value.current_teamsize_order);
    out.write_num<uint32_t>(value.current_teamsize_chaos);
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

void ProtoVer::read(Data_in& in, PKT_C2S_Ping_Load_Info& value) const {
    in.read_num<uint32_t>(value.fromID);
    read(in, value.mConnectionInfo);
}
void ProtoVer::write(Data_out& out, PKT_C2S_Ping_Load_Info const& value) const {
    out.write_num<uint32_t>(value.fromID);
    write(out, value.mConnectionInfo);
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

void ProtoVer::read(Data_in& in, PKT_S2C_CreateHero& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint32_t>(value.netObjID);
    in.read_num<uint8_t>(value.netNodeID);
    in.read_num<uint32_t>(value.playerUID);
    in.read_num<bool>(value.teamIsOrder);
    in.read_num<bool>(value.isBot);
    in.read_fstr<40>(value.Name);
    in.read_fstr<40>(value.Skin);
}
void ProtoVer::write(Data_out& out, PKT_S2C_CreateHero const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint32_t>(value.netObjID);
    out.write_num<uint8_t>(value.netNodeID);
    out.write_num<uint32_t>(value.playerUID);
    out.write_num<bool>(value.teamIsOrder);
    out.write_num<bool>(value.isBot);
    out.write_fstr<40>(value.Name);
    out.write_fstr<40>(value.Skin);
}

void ProtoVer::read(Data_in& in, PKT_S2C_CreateTurret& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<uint32_t>(value.netObjID);
    in.read_num<uint8_t>(value.netNodeID);
    in.read_fstr<64>(value.Name);
}
void ProtoVer::write(Data_out& out, PKT_S2C_CreateTurret const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<uint32_t>(value.netObjID);
    out.write_num<uint8_t>(value.netNodeID);
    out.write_fstr<64>(value.Name);
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
    in.read_fstr<256>(value.mVersionString);
}
void ProtoVer::write(Data_out& out, PKT_SynchVersionC2S const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<float>(value.mTime_LastClient);
    out.write_num<uint32_t>(value.mClientNetID);
    out.write_fstr<256>(value.mVersionString);
}

void ProtoVer::read(Data_in& in, PKT_SynchVersionS2C& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_num<bool>(value.mIsVersionOk);
    in.read_num<int32_t>(value.mMapToLoad);
    for(auto& elem: value.playerInfo) {
        read(in, elem);
    }
    in.read_fstr<256>(value.mVersionString);
}
void ProtoVer::write(Data_out& out, PKT_SynchVersionS2C const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_num<bool>(value.mIsVersionOk);
    out.write_num<int32_t>(value.mMapToLoad);
    for(auto const& elem: value.playerInfo) {
        write(out, elem);
    }
    out.write_fstr<256>(value.mVersionString);
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

void ProtoVer::read(Data_in& in, PKT_S2C_FaceDirection& value) const {
    in.read_num<uint32_t>(value.fromID);
    in.read_point3d(value.direction);
}
void ProtoVer::write(Data_out& out, PKT_S2C_FaceDirection const& value) const {
    out.write_num<uint32_t>(value.fromID);
    out.write_point3d(value.direction);
}
