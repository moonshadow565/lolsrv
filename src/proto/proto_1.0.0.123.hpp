#pragma once
#include "proto_1.0.0.122.hpp"

IMPL_PROTO_VER(PROTO_VER(1.0.0.123), PROTO_VER(1.0.0.122)) {
public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;

    void read(Data_in & io, PKT_C2S_MapPing & value) const override;
    void write(Data_out & io, PKT_C2S_MapPing const& value) const override;

    void read(Data_in & io, PKT_S2C_MapPing & value) const override;
    void write(Data_out & io, PKT_S2C_MapPing const& value) const override;
};
