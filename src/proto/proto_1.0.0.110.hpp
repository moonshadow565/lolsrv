#pragma once
#include "proto_1.0.0.109.hpp"

IMPL_PROTO_VER(PROTO_VER(1.0.0.110), PROTO_VER(1.0.0.109)) {
    public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;

    Span<ProtoNameID const> pkt_array() const override;

    void read(Data_in& in, PlayerLiteInfo& value) const override;
    void write(Data_out& out, PlayerLiteInfo const& value) const override;
};
