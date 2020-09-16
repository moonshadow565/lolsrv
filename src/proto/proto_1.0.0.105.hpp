#pragma once
#include "proto_1.0.0.104.hpp"

IMPL_PROTO_VER(PROTO_VER(1.0.0.105), PROTO_VER(1.0.0.104)) {
public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;

    Span<ProtoNameID const> pkt_array() const override;

    void read(Data_in & io, PKT_S2C_CreateHero & value) const override;
    void write(Data_out & io, PKT_S2C_CreateHero const& value) const override;
};
