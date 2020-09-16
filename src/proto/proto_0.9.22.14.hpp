#pragma once
#include "proto_0.8.13.26.hpp"

IMPL_PROTO_VER(PROTO_VER(0.9.22.14), PROTO_VER(0.8.13.26)) {
public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;

    Span<ProtoNameID const> pkt_array() const override;

    void read(Data_in & io, PKT_ID & value) const override;
    void write(Data_out & io, PKT_ID const& value) const override;

    void read(Data_in & io, EGP_Chat & value) const override;
    void write(Data_out & io, EGP_Chat const& value) const override;

    void read(Data_in & io, PKT_S2C_CreateHero & value) const override;
    void write(Data_out & io, PKT_S2C_CreateHero const& value) const override;

    void read(Data_in & io, PKT_S2C_ToggleFoW & value) const override;
    void write(Data_out & io, PKT_S2C_ToggleFoW const& value) const override;
};
