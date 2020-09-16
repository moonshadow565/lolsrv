#pragma once
#include "proto_1.0.0.123.hpp"

IMPL_PROTO_VER(PROTO_VER(1.0.0.124), PROTO_VER(1.0.0.123)) {
public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;

    Span<ProtoNameID const> pkt_array() const override;

    void read(Data_in & io, PlayerLiteInfo & value) const override;
    void write(Data_out & io, PlayerLiteInfo const& value) const override;

    void read(Data_in & io, PKT_S2C_StartGame & value) const override;
    void write(Data_out & io, PKT_S2C_StartGame const& value) const override;
};
