#pragma once
#include "proto_0.9.22.18.hpp"

IMPL_PROTO_VER(PROTO_VER(0.9.25.21), PROTO_VER(0.9.22.18)) {
public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;

    Span<ProtoNameID const> pkt_array() const override;

    void read(Data_in & io, PKT_S2C_CreateHero & value) const override;
    void write(Data_out & io, PKT_S2C_CreateHero const& value) const override;

    void read(Data_in & io, PKT_SynchVersionS2C & value) const override;
    void write(Data_out & io, PKT_SynchVersionS2C const& value) const override;
};
