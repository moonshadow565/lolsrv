#pragma once
#include "proto_1.0.0.130.hpp"

IMPL_PROTO_VER(PROTO_VER(1.0.0.131), PROTO_VER(1.0.0.130)) {
    public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;

    Span<ProtoNameID const> pkt_array() const override;

    void read(Data_in& in, PKT_S2C_CreateHero& value) const override;
    void write(Data_out& out, PKT_S2C_CreateHero const& value) const override;
};
