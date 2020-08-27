#pragma once
#include "proto_base.hpp"

IMPL_PROTO_VER(PROTO_VER(0.8.13.26), ProtoBase) {
    public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;

    Span<ProtoNameID const> egp_array() const override;

    Span<ProtoNameID const> pkt_array() const override;

    void read(Data_in& in, EGP_ID& value) const override;
    void write(Data_out& out, EGP_ID const& value) const override;

    void read(Data_in& in, PKT_ID& value) const override;
    void write(Data_out& out, PKT_ID const& value) const override;

    void read(Data_in& in, EGP_RequestJoinTeam& value) const override;
    void write(Data_out& out, EGP_RequestJoinTeam const& value) const override;

    void read(Data_in& in, EGP_RequestRename& value) const override;
    void write(Data_out& out, EGP_RequestRename const& value) const override;

    void read(Data_in& in, EGP_RequestReskin& value) const override;
    void write(Data_out& out, EGP_RequestReskin const& value) const override;

    void read(Data_in& in, EGP_TeamRosterUpdate& value) const override;
    void write(Data_out& out, EGP_TeamRosterUpdate const& value) const override;

    void read(Data_in& in, EGP_Chat& value) const override;
    void write(Data_out& out, EGP_Chat const& value) const override;

    void read(Data_in& in, CommonBasicAttack& value) const override;
    void write(Data_out& out, CommonBasicAttack const& value) const override;

    void read(Data_in& in, ConnectionInfo& value) const override;
    void write(Data_out& out, ConnectionInfo const& value) const override;

    void read(Data_in& in, PlayerLiteInfo& value) const override;
    void write(Data_out& out, PlayerLiteInfo const& value) const override;

    void read(Data_in& in, PKT_Basic_Attack& value) const override;
    void write(Data_out& out, PKT_Basic_Attack const& value) const override;

    void read(Data_in& in, PKT_Basic_Attack_Pos& value) const override;
    void write(Data_out& out, PKT_Basic_Attack_Pos const& value) const override;

    void read(Data_in& in, PKT_BuyItemAns& value) const override;
    void write(Data_out& out, PKT_BuyItemAns const& value) const override;

    void read(Data_in& in, PKT_BuyItemReq& value) const override;
    void write(Data_out& out, PKT_BuyItemReq const& value) const override;

    void read(Data_in& in, PKT_C2S_CharSelected& value) const override;
    void write(Data_out& out, PKT_C2S_CharSelected const& value) const override;

    void read(Data_in& in, PKT_C2S_ClientReady& value) const override;
    void write(Data_out& out, PKT_C2S_ClientReady const& value) const override;

    void read(Data_in& in, PKT_C2S_MapPing& value) const override;
    void write(Data_out& out, PKT_C2S_MapPing const& value) const override;

    void read(Data_in& in, PKT_C2S_Ping_Load_Info& value) const override;
    void write(Data_out& out, PKT_C2S_Ping_Load_Info const& value) const override;

    void read(Data_in& in, PKT_C2S_PlayEmote& value) const override;
    void write(Data_out& out, PKT_C2S_PlayEmote const& value) const override;

    void read(Data_in& in, PKT_C2S_QueryStatusReq& value) const override;
    void write(Data_out& out, PKT_C2S_QueryStatusReq const& value) const override;

    void read(Data_in& in, PKT_C2S_Reconnect& value) const override;
    void write(Data_out& out, PKT_C2S_Reconnect const& value) const override;

    void read(Data_in& in, PKT_NPC_Die& value) const override;
    void write(Data_out& out, PKT_NPC_Die const& value) const override;

    void read(Data_in& in, PKT_NPC_IssueOrderReq& value) const override;
    void write(Data_out& out, PKT_NPC_IssueOrderReq const& value) const override;

    void read(Data_in& in, PKT_NPC_LevelUp& value) const override;
    void write(Data_out& out, PKT_NPC_LevelUp const& value) const override;

    void read(Data_in& in, PKT_NPC_UpgradeSpellAns& value) const override;
    void write(Data_out& out, PKT_NPC_UpgradeSpellAns const& value) const override;

    void read(Data_in& in, PKT_NPC_UpgradeSpellReq& value) const override;
    void write(Data_out& out, PKT_NPC_UpgradeSpellReq const& value) const override;

    void read(Data_in& in, PKT_OnEnterVisiblityClient& value) const override;
    void write(Data_out& out, PKT_OnEnterVisiblityClient const& value) const override;

    void read(Data_in& in, PKT_RemoveItemAns& value) const override;
    void write(Data_out& out, PKT_RemoveItemAns const& value) const override;

    void read(Data_in& in, PKT_RemoveItemReq& value) const override;
    void write(Data_out& out, PKT_RemoveItemReq const& value) const override;

    void read(Data_in& in, PKT_S2C_ChangeCharacterData& value) const override;
    void write(Data_out& out, PKT_S2C_ChangeCharacterData const& value) const override;

    void read(Data_in& in, PKT_S2C_CreateHero& value) const override;
    void write(Data_out& out, PKT_S2C_CreateHero const& value) const override;

    void read(Data_in& in, PKT_S2C_CreateTurret& value) const override;
    void write(Data_out& out, PKT_S2C_CreateTurret const& value) const override;

    void read(Data_in& in, PKT_S2C_FaceDirection& value) const override;
    void write(Data_out& out, PKT_S2C_FaceDirection const& value) const override;

    void read(Data_in& in, PKT_S2C_EndSpawn& value) const override;
    void write(Data_out& out, PKT_S2C_EndSpawn const& value) const override;

    void read(Data_in& in, PKT_S2C_MapPing& value) const override;
    void write(Data_out& out, PKT_S2C_MapPing const& value) const override;

    void read(Data_in& in, PKT_S2C_Ping_Load_Info& value) const override;
    void write(Data_out& out, PKT_S2C_Ping_Load_Info const& value) const override;

    void read(Data_in& in, PKT_S2C_PlayAnimation& value) const override;
    void write(Data_out& out, PKT_S2C_PlayAnimation const& value) const override;

    void read(Data_in& in, PKT_S2C_PlayEmote& value) const override;
    void write(Data_out& out, PKT_S2C_PlayEmote const& value) const override;

    void read(Data_in& in, PKT_S2C_QueryStatusAns& value) const override;
    void write(Data_out& out, PKT_S2C_QueryStatusAns const& value) const override;

    void read(Data_in& in, PKT_S2C_Reconnect& value) const override;
    void write(Data_out& out, PKT_S2C_Reconnect const& value) const override;

    void read(Data_in& in, PKT_S2C_StartGame& value) const override;
    void write(Data_out& out, PKT_S2C_StartGame const& value) const override;

    void read(Data_in& in, PKT_S2C_StartSpawn& value) const override;
    void write(Data_out& out, PKT_S2C_StartSpawn const& value) const override;

    void read(Data_in& in, PKT_SwapItemAns& value) const override;
    void write(Data_out& out, PKT_SwapItemAns const& value) const override;

    void read(Data_in& in, PKT_SwapItemReq& value) const override;
    void write(Data_out& out, PKT_SwapItemReq const& value) const override;

    void read(Data_in& in, PKT_SynchVersionC2S& value) const override;
    void write(Data_out& out, PKT_SynchVersionC2S const& value) const override;

    void read(Data_in& in, PKT_SynchVersionS2C& value) const override;
    void write(Data_out& out, PKT_SynchVersionS2C const& value) const override;

    void read(Data_in& in, PKT_WaypointList& value) const override;
    void write(Data_out& out, PKT_WaypointList const& value) const override;

    void read(Data_in& in, PKT_World_LockCamera_Server& value) const override;
    void write(Data_out& out, PKT_World_LockCamera_Server const& value) const override;

    void read(Data_in& in, PKT_World_SendCamera_Server& value) const override;
    void write(Data_out& out, PKT_World_SendCamera_Server const& value) const override;

    void read(Data_in& in, PKT_World_SendCamera_Server_Acknologment& value) const override;
    void write(Data_out& out, PKT_World_SendCamera_Server_Acknologment const& value) const override;
};
