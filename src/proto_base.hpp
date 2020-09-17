#pragma once
#include "proto_pkt.hpp"

#include <log.hpp>
#include <span.hpp>
#include <stdexcept>

/// Errors

struct ProtoError : public std::exception {};

struct ProtoErrorNoID : public ProtoError {
    std::string name;
    inline ProtoErrorNoID(std::string_view aname) noexcept : name(aname) {}
};

struct ProtoErrorUnknownID : public ProtoError {
    uint16_t id;
    inline ProtoErrorUnknownID(uint16_t aid) noexcept : id(aid) {}
};

struct ProtoErrorReadNotImpl : public ProtoError {
    std::string name;
    inline ProtoErrorReadNotImpl(std::string_view aname) noexcept : name(aname) {}
};

struct ProtoErrorWriteNotImpl : public ProtoError {
    std::string name;
    inline ProtoErrorWriteNotImpl(std::string_view aname) noexcept : name(aname) {}
};

struct ProtoErrorIO : public ProtoError {
    std::string name;
    ptrdiff_t position;
    inline ProtoErrorIO(std::string_view aname, ptrdiff_t aposition) noexcept : name(aname), position(aposition) {}
};

struct ProtoErrorBadChannel : public ProtoError {
    uint32_t channel;
    inline ProtoErrorBadChannel(uint32_t achannel) noexcept : channel(achannel) {}
};

/// Utils
inline constexpr uint32_t ver(char const* str) noexcept {
    uint32_t h = 0x811c9dc5u;
    while (*str) {
        h *= 0x01000193u;
        h ^= (uint8_t)*str++;
    }
    return h;
}

#define PROTO_VER(v) ProtoVersion<ver(#v)>
#define IMPL_PROTO_VER(v, from) \
    template <>                 \
    struct v : public from
#define READ_NOT_IMPL                                                                                         \
    {                                                                                                         \
        (void)io;                                                                                             \
        throw ProtoErrorReadNotImpl(type_name<std::remove_cv_t<std::remove_reference_t<decltype(value)>>>()); \
    }
#define WRITE_NOT_IMPL                                                                                         \
    {                                                                                                          \
        (void)io;                                                                                              \
        throw ProtoErrorWriteNotImpl(type_name<std::remove_cv_t<std::remove_reference_t<decltype(value)>>>()); \
    }

/// Protocol
struct ProtoNameID {
    std::string_view name = {};
    uint16_t id = {};
};

template <uint32_t...>
struct ProtoVersion;

struct ProtoBase {
public:
    virtual std::string_view name() const = 0;

    virtual Span<ProtoNameID const> egp_array() const = 0;
    virtual Span<ProtoNameID const> pkt_array() const = 0;

    virtual void read(Data_in& io, EGP_ID& value) const;
    virtual void write(Data_out& io, EGP_ID const& value) const;

    virtual void read(Data_in& io, PKT_ID& value) const;
    virtual void write(Data_out& io, PKT_ID const& value) const;

    virtual void read(Data_in& io, EGP_RequestJoinTeam& value) const;
    virtual void write(Data_out& io, EGP_RequestJoinTeam const& value) const;

    virtual void read(Data_in& io, EGP_RequestRename& value) const;
    virtual void write(Data_out& io, EGP_RequestRename const& value) const;

    virtual void read(Data_in& io, EGP_RequestReskin& value) const;
    virtual void write(Data_out& io, EGP_RequestReskin const& value) const;

    virtual void read(Data_in& io, EGP_TeamRosterUpdate& value) const;
    virtual void write(Data_out& io, EGP_TeamRosterUpdate const& value) const;

    virtual void read(Data_in& io, EGP_Chat& value) const;
    virtual void write(Data_out& io, EGP_Chat const& value) const;

    virtual void read(Data_in& io, CommonBasicAttack& value) const;
    virtual void write(Data_out& io, CommonBasicAttack const& value) const;

    virtual void read(Data_in& io, ConnectionInfo& value) const;
    virtual void write(Data_out& io, ConnectionInfo const& value) const;

    virtual void read(Data_in& io, PlayerLiteInfo& value) const;
    virtual void write(Data_out& io, PlayerLiteInfo const& value) const;

    virtual void read(Data_in& io, PKT_Basic_Attack& value) const;
    virtual void write(Data_out& io, PKT_Basic_Attack const& value) const;

    virtual void read(Data_in& io, PKT_Basic_Attack_Pos& value) const;
    virtual void write(Data_out& io, PKT_Basic_Attack_Pos const& value) const;

    virtual void read(Data_in& io, PKT_BuyItemAns& value) const;
    virtual void write(Data_out& io, PKT_BuyItemAns const& value) const;

    virtual void read(Data_in& io, PKT_BuyItemReq& value) const;
    virtual void write(Data_out& io, PKT_BuyItemReq const& value) const;

    virtual void read(Data_in& io, PKT_C2S_CharSelected& value) const;
    virtual void write(Data_out& io, PKT_C2S_CharSelected const& value) const;

    virtual void read(Data_in& io, PKT_C2S_ClientReady& value) const;
    virtual void write(Data_out& io, PKT_C2S_ClientReady const& value) const;

    virtual void read(Data_in& io, PKT_C2S_MapPing& value) const;
    virtual void write(Data_out& io, PKT_C2S_MapPing const& value) const;

    virtual void read(Data_in& io, PKT_C2S_Ping_Load_Info& value) const;
    virtual void write(Data_out& io, PKT_C2S_Ping_Load_Info const& value) const;

    virtual void read(Data_in& io, PKT_C2S_PlayEmote& value) const;
    virtual void write(Data_out& io, PKT_C2S_PlayEmote const& value) const;

    virtual void read(Data_in& io, PKT_C2S_QueryStatusReq& value) const;
    virtual void write(Data_out& io, PKT_C2S_QueryStatusReq const& value) const;

    virtual void read(Data_in& io, PKT_C2S_Reconnect& value) const;
    virtual void write(Data_out& io, PKT_C2S_Reconnect const& value) const;

    virtual void read(Data_in& io, PKT_NPC_Die& value) const;
    virtual void write(Data_out& io, PKT_NPC_Die const& value) const;

    virtual void read(Data_in& io, PKT_NPC_LevelUp& value) const;
    virtual void write(Data_out& io, PKT_NPC_LevelUp const& value) const;

    virtual void read(Data_in& io, PKT_NPC_IssueOrderReq& value) const;
    virtual void write(Data_out& io, PKT_NPC_IssueOrderReq const& value) const;

    virtual void read(Data_in& io, PKT_NPC_UpgradeSpellAns& value) const;
    virtual void write(Data_out& io, PKT_NPC_UpgradeSpellAns const& value) const;

    virtual void read(Data_in& io, PKT_NPC_UpgradeSpellReq& value) const;
    virtual void write(Data_out& io, PKT_NPC_UpgradeSpellReq const& value) const;

    virtual void read(Data_in& io, PKT_OnEnterVisiblityClient& value) const;
    virtual void write(Data_out& io, PKT_OnEnterVisiblityClient const& value) const;

    virtual void read(Data_in& io, PKT_RemoveItemAns& value) const;
    virtual void write(Data_out& io, PKT_RemoveItemAns const& value) const;

    virtual void read(Data_in& io, PKT_RemoveItemReq& value) const;
    virtual void write(Data_out& io, PKT_RemoveItemReq const& value) const;

    virtual void read(Data_in& io, PKT_S2C_ChangeCharacterData& value) const;
    virtual void write(Data_out& io, PKT_S2C_ChangeCharacterData const& value) const;

    virtual void read(Data_in& io, PKT_S2C_CreateHero& value) const;
    virtual void write(Data_out& io, PKT_S2C_CreateHero const& value) const;

    virtual void read(Data_in& io, PKT_S2C_CreateTurret& value) const;
    virtual void write(Data_out& io, PKT_S2C_CreateTurret const& value) const;

    virtual void read(Data_in& io, PKT_S2C_FaceDirection& value) const;
    virtual void write(Data_out& io, PKT_S2C_FaceDirection const& value) const;

    virtual void read(Data_in& io, PKT_S2C_EndSpawn& value) const;
    virtual void write(Data_out& io, PKT_S2C_EndSpawn const& value) const;

    virtual void read(Data_in& io, PKT_S2C_MapPing& value) const;
    virtual void write(Data_out& io, PKT_S2C_MapPing const& value) const;

    virtual void read(Data_in& io, PKT_S2C_Ping_Load_Info& value) const;
    virtual void write(Data_out& io, PKT_S2C_Ping_Load_Info const& value) const;

    virtual void read(Data_in& io, PKT_S2C_PlayAnimation& value) const;
    virtual void write(Data_out& io, PKT_S2C_PlayAnimation const& value) const;

    virtual void read(Data_in& io, PKT_S2C_PlayEmote& value) const;
    virtual void write(Data_out& io, PKT_S2C_PlayEmote const& value) const;

    virtual void read(Data_in& io, PKT_S2C_QueryStatusAns& value) const;
    virtual void write(Data_out& io, PKT_S2C_QueryStatusAns const& value) const;

    virtual void read(Data_in& io, PKT_S2C_Reconnect& value) const;
    virtual void write(Data_out& io, PKT_S2C_Reconnect const& value) const;

    virtual void read(Data_in& io, PKT_S2C_StartGame& value) const;
    virtual void write(Data_out& io, PKT_S2C_StartGame const& value) const;

    virtual void read(Data_in& io, PKT_S2C_StartSpawn& value) const;
    virtual void write(Data_out& io, PKT_S2C_StartSpawn const& value) const;

    virtual void read(Data_in& io, PKT_S2C_ToggleFoW& value) const;
    virtual void write(Data_out& io, PKT_S2C_ToggleFoW const& value) const;

    virtual void read(Data_in& io, PKT_SpawnMinionS2C& value) const;
    virtual void write(Data_out& io, PKT_SpawnMinionS2C const& value) const;

    virtual void read(Data_in& io, PKT_SwapItemAns& value) const;
    virtual void write(Data_out& io, PKT_SwapItemAns const& value) const;

    virtual void read(Data_in& io, PKT_SwapItemReq& value) const;
    virtual void write(Data_out& io, PKT_SwapItemReq const& value) const;

    virtual void read(Data_in& io, PKT_SynchVersionC2S& value) const;
    virtual void write(Data_out& io, PKT_SynchVersionC2S const& value) const;

    virtual void read(Data_in& io, PKT_SynchVersionS2C& value) const;
    virtual void write(Data_out& io, PKT_SynchVersionS2C const& value) const;

    virtual void read(Data_in& io, PKT_WaypointList& value) const;
    virtual void write(Data_out& io, PKT_WaypointList const& value) const;

    virtual void read(Data_in& io, PKT_World_LockCamera_Server& value) const;
    virtual void write(Data_out& io, PKT_World_LockCamera_Server const& value) const;

    virtual void read(Data_in& io, PKT_World_SendCamera_Server& value) const;
    virtual void write(Data_out& io, PKT_World_SendCamera_Server const& value) const;

    virtual void read(Data_in& io, PKT_World_SendCamera_Server_Acknologment& value) const;
    virtual void write(Data_out& io, PKT_World_SendCamera_Server_Acknologment const& value) const;

    ProtoNameID const& find_info(std::string_view name, bool is_payload) const;

    ProtoNameID const& find_info(uint16_t id, bool is_payload) const;

    PKT_C2S read_pkt(Data_in io, Channel channel) const;
    std::vector<char> write_pkt(PKT_S2C const& pkt) const;
};
