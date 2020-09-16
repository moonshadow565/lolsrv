#pragma once
#include "proto_1.0.0.102.hpp"

IMPL_PROTO_VER(PROTO_VER(1.0.0.103), PROTO_VER(1.0.0.102)) {
public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;

    Span<ProtoNameID const> pkt_array() const override;

    void read(Data_in & io, PKT_NPC_Die & value) const override;
    void write(Data_out & io, PKT_NPC_Die const& value) const override;
};
