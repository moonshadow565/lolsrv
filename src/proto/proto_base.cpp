#include "proto_base.hpp"

using ProtoVer = ProtoBase;

void ProtoVer::read(Data_in& in, EGP_ID& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, EGP_ID const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_ID& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_ID const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, EGP_RequestJoinTeam& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, EGP_RequestJoinTeam const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, EGP_RequestRename& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, EGP_RequestRename const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, EGP_RequestReskin& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, EGP_RequestReskin const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, EGP_TeamRosterUpdate& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, EGP_TeamRosterUpdate const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, ConnectionInfo& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, ConnectionInfo const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PlayerLiteInfo& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PlayerLiteInfo const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_C2S_CharSelected& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_C2S_CharSelected const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_C2S_ClientReady& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_C2S_ClientReady const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_C2S_Ping_Load_Info& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_C2S_Ping_Load_Info const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_C2S_QueryStatusReq& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_C2S_QueryStatusReq const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_C2S_Reconnect& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_C2S_Reconnect const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_NPC_IssueOrderReq& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_NPC_IssueOrderReq const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_OnEnterVisiblityClient& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_OnEnterVisiblityClient const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_S2C_CreateHero& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_S2C_CreateHero const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_S2C_CreateTurret& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_S2C_CreateTurret const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_S2C_EndSpawn& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_S2C_EndSpawn const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_S2C_Ping_Load_Info& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_S2C_Ping_Load_Info const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_S2C_QueryStatusAns& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_S2C_QueryStatusAns const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_S2C_Reconnect& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_S2C_Reconnect const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_S2C_StartGame& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_S2C_StartGame const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_S2C_StartSpawn& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_S2C_StartSpawn const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_SynchVersionC2S& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_SynchVersionC2S const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_SynchVersionS2C& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_SynchVersionS2C const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_WaypointList& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_WaypointList const& value) const WRITE_NOT_IMPL

void ProtoVer::read(Data_in& in, PKT_S2C_FaceDirection& value) const READ_NOT_IMPL
void ProtoVer::write(Data_out& out, PKT_S2C_FaceDirection const& value) const WRITE_NOT_IMPL

template<typename T, typename...V>
inline bool read_impl_one(ProtoVer const* proto, Data_in& in, std::string_view name, std::variant<V...>& value) {
    if (name == type_name<T>()) {
        T result = {};
        proto->read(in, result);
        value = std::move(result);
        return true;
    } else {
        return false;
    }
}

template<typename...V>
inline bool read_impl(ProtoVer const* proto, Data_in& in, std::string_view name, std::variant<V...>& value) {
    return (read_impl_one<V>(proto, in, name, value) || ...);
}

PKT_C2S ProtoVer::read_pkt(Data_in in, Channel channel) const {
    uint16_t id = {};
    bool is_payload = false;
    PKT_ID pkt_id = {};
    EGP_ID egp_id = {};
    try {
        switch(channel) {
        case CHANNEL_GENERIC_APP_TO_SERVER:
        case CHANNEL_SYNCHCLOCK:
        case CHANNEL_GENERIC_APP_BROADCAST:
        case CHANNEL_GENERIC_APP_BROADCAST_UNRELIABLE:
            read(in, pkt_id);
            id = static_cast<uint16_t>(pkt_id);
            is_payload = false;
            break;
        case CHANNEL_MIDDLE_TIER_ROSTER:
            read(in, egp_id);
            id = static_cast<uint16_t>(egp_id);
            is_payload = true;
            break;
        default:
            throw ProtoErrorBadChannel(channel);
        }
    } catch (IOError const& err) {
        throw ProtoErrorIO("id", err.position);
    }
    auto const table = is_payload ? egp_array() : pkt_array();
    auto const info = std::find_if(table.begin(), table.end(), [&](auto const& info) { return info.id == id; });
    if (info == table.end()) {
        throw ProtoErrorUnknownID(id, channel);
    }
    PKT_C2S value = {};
    if (!read_impl(this, in, info->name, value)) {
        throw ProtoErrorReadNotImpl(info->name);
    }
    return value;
}

std::vector<char> ProtoVer::write_pkt(PKT_S2C const& pkt) const {
    return std::visit([this](auto const& pkt) {
        using T = std::remove_cvref_t<decltype(pkt)>;
        constexpr auto name = type_name<T>();
        constexpr auto is_payload = !std::is_base_of_v<DefaultPacket, T>;
        Span<ProtoNameID const> const table =  is_payload ? egp_array() : pkt_array();
        auto const info = std::find_if(table.begin(), table.end(), [&](auto const& info) { return info.name == name; });
        if (info == table.end()) {
            throw ProtoErrorNoID(name);
        }
        try {
            Data_out out = {};
            if constexpr (is_payload) {
                write(out, static_cast<EGP_ID>(info->id));
            } else {
                write(out, static_cast<PKT_ID>(info->id));
            }
            write(out, pkt);
            return out.buffer;
        } catch(IOError const& err) {
            throw ProtoErrorIO(name, err.position);
        }
    }, pkt);
}
