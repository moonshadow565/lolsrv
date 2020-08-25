#pragma once
#include <stdexcept>
#include <span.hpp>
#include <log.hpp>
#include "pkt.hpp"

/// Errors

struct ProtoError : public std::exception {};

struct ProtoErrorNoID : public ProtoError {
    std::string name;
    inline ProtoErrorNoID(std::string_view aname) noexcept
        : name(aname) {}
};

struct ProtoErrorUnknownID : public ProtoError {
    uint16_t id;
    Channel channel;
    inline ProtoErrorUnknownID(uint16_t aid, Channel achannel) noexcept
        : id(aid), channel(achannel) {}
};

struct ProtoErrorReadNotImpl : public ProtoError {
    std::string name;
    inline ProtoErrorReadNotImpl(std::string_view aname) noexcept
        : name(aname) {}
};

struct ProtoErrorWriteNotImpl : public ProtoError {
    std::string name;
    inline ProtoErrorWriteNotImpl(std::string_view aname) noexcept
        : name(aname) {}
};

struct ProtoErrorIO : public ProtoError {
    std::string name;
    ptrdiff_t position;
    inline ProtoErrorIO(std::string_view aname, ptrdiff_t aposition) noexcept
        : name(aname), position(aposition) {}
};

struct ProtoErrorBadChannel : public ProtoError {
    uint32_t channel;
    inline ProtoErrorBadChannel(uint32_t achannel) noexcept
        : channel(achannel) {}
};

/// Utils
template <typename T>
inline constexpr std::string_view type_name() {
    std::string_view name, prefix, suffix;
#ifdef __clang__
    name = __PRETTY_FUNCTION__;
    prefix = "std::string_view type_name() [T = ";
    suffix = "]";
#elif defined(__GNUC__)
    name = __PRETTY_FUNCTION__;
    prefix = "constexpr std::string_view type_name() [with T = ";
    suffix = "; std::string_view = std::basic_string_view<char>]";
#elif defined(_MSC_VER)
    name = __FUNCSIG__;
    prefix = "class std::basic_string_view<char,struct std::char_traits<char> > __cdecl type_name<struct ";
    suffix = ">(void)";
#endif
    name.remove_prefix(prefix.size());
    name.remove_suffix(suffix.size());
    return name;
}

inline constexpr uint32_t ver(char const* str) noexcept {
    uint32_t h = 0x811c9dc5u;
    while (*str) {
        h *= 0x01000193u;
        h ^= (uint8_t)*str++;
    }
    return h;
}

#define PROTO_VER(v) ProtoVersion<ver(#v)>
#define IMPL_PROTO_VER(v, from) template<> struct v : public from
#define READ_NOT_IMPL { (void)in; throw ProtoErrorReadNotImpl(type_name<std::remove_cv_t<std::remove_reference_t<decltype(value)>>>()); }
#define WRITE_NOT_IMPL { (void)out; throw ProtoErrorWriteNotImpl(type_name<std::remove_cv_t<std::remove_reference_t<decltype(value)>>>()); }

/// Protocol
struct ProtoNameID {
    std::string_view name = {};
    uint16_t id = {};
};


template<uint32_t...>
struct ProtoVersion;

struct ProtoBase {
public:
    virtual std::string_view name() const = 0;

    virtual Span<ProtoNameID const> egp_array() const = 0;
    virtual Span<ProtoNameID const> pkt_array() const = 0;

    virtual void read(Data_in& in, EGP_ID& value) const;
    virtual void write(Data_out& out, EGP_ID const& value) const;

    virtual void read(Data_in& in, PKT_ID& value) const;
    virtual void write(Data_out& out, PKT_ID const& value) const;

    virtual void read(Data_in& in, EGP_RequestJoinTeam& value) const;
    virtual void write(Data_out& out, EGP_RequestJoinTeam const& value) const;

    virtual void read(Data_in& in, EGP_RequestRename& value) const;
    virtual void write(Data_out& out, EGP_RequestRename const& value) const;

    virtual void read(Data_in& in, EGP_RequestReskin& value) const;
    virtual void write(Data_out& out, EGP_RequestReskin const& value) const;

    virtual void read(Data_in& in, EGP_TeamRosterUpdate& value) const;
    virtual void write(Data_out& out, EGP_TeamRosterUpdate const& value) const;

    virtual void read(Data_in& in, ConnectionInfo& value) const;
    virtual void write(Data_out& out, ConnectionInfo const& value) const;

    virtual void read(Data_in& in, PlayerLiteInfo& value) const;
    virtual void write(Data_out& out, PlayerLiteInfo const& value) const;

    virtual void read(Data_in& in, PKT_C2S_CharSelected& value) const;
    virtual void write(Data_out& out, PKT_C2S_CharSelected const& value) const;

    virtual void read(Data_in& in, PKT_C2S_ClientReady& value) const;
    virtual void write(Data_out& out, PKT_C2S_ClientReady const& value) const;

    virtual void read(Data_in& in, PKT_C2S_Ping_Load_Info& value) const;
    virtual void write(Data_out& out, PKT_C2S_Ping_Load_Info const& value) const;

    virtual void read(Data_in& in, PKT_C2S_QueryStatusReq& value) const;
    virtual void write(Data_out& out, PKT_C2S_QueryStatusReq const& value) const;

    virtual void read(Data_in& in, PKT_C2S_Reconnect& value) const;
    virtual void write(Data_out& out, PKT_C2S_Reconnect const& value) const;

    virtual void read(Data_in& in, PKT_NPC_IssueOrderReq& value) const;
    virtual void write(Data_out& out, PKT_NPC_IssueOrderReq const& value) const;

    virtual void read(Data_in& in, PKT_OnEnterVisiblityClient& value) const;
    virtual void write(Data_out& out, PKT_OnEnterVisiblityClient const& value) const;

    virtual void read(Data_in& in, PKT_S2C_CreateHero& value) const;
    virtual void write(Data_out& out, PKT_S2C_CreateHero const& value) const;

    virtual void read(Data_in& in, PKT_S2C_CreateTurret& value) const;
    virtual void write(Data_out& out, PKT_S2C_CreateTurret const& value) const;

    virtual void read(Data_in& in, PKT_S2C_EndSpawn& value) const;
    virtual void write(Data_out& out, PKT_S2C_EndSpawn const& value) const;

    virtual void read(Data_in& in, PKT_S2C_Ping_Load_Info& value) const;
    virtual void write(Data_out& out, PKT_S2C_Ping_Load_Info const& value) const;

    virtual void read(Data_in& in, PKT_S2C_QueryStatusAns& value) const;
    virtual void write(Data_out& out, PKT_S2C_QueryStatusAns const& value) const;

    virtual void read(Data_in& in, PKT_S2C_Reconnect& value) const;
    virtual void write(Data_out& out, PKT_S2C_Reconnect const& value) const;

    virtual void read(Data_in& in, PKT_S2C_StartGame& value) const;
    virtual void write(Data_out& out, PKT_S2C_StartGame const& value) const;

    virtual void read(Data_in& in, PKT_S2C_StartSpawn& value) const;
    virtual void write(Data_out& out, PKT_S2C_StartSpawn const& value) const;

    virtual void read(Data_in& in, PKT_SynchVersionC2S& value) const;
    virtual void write(Data_out& out, PKT_SynchVersionC2S const& value) const;

    virtual void read(Data_in& in, PKT_SynchVersionS2C& value) const;
    virtual void write(Data_out& out, PKT_SynchVersionS2C const& value) const;

    virtual void read(Data_in& in, PKT_WaypointList& value) const;
    virtual void write(Data_out& out, PKT_WaypointList const& value) const;

    virtual void read(Data_in& in, PKT_S2C_FaceDirection& value) const;
    virtual void write(Data_out& out, PKT_S2C_FaceDirection const& value) const;

    PKT_C2S read_pkt(Data_in in, Channel channel) const;
    std::vector<char> write_pkt(PKT_S2C const& pkt) const;
};

