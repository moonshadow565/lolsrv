#pragma once
#include "proto_0.9.25.24.hpp"

IMPL_PROTO_VER(PROTO_VER(0.9.25.36), PROTO_VER(0.9.25.24)) {
public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;

    Span<ProtoNameID const> pkt_array() const override;

    void read(Data_in & io, PKT_S2C_ChangeCharacterData & value) const override;
    void write(Data_out & io, PKT_S2C_ChangeCharacterData const& value) const override;
};
