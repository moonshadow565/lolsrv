#pragma once
#include "proto_1.0.0.75.hpp"

IMPL_PROTO_VER(PROTO_VER(1.0.0.79), PROTO_VER(1.0.0.75)) {
    public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;

    Span<ProtoNameID const> pkt_array() const override;

    void read(Data_in& in, PKT_ID& value) const override;
    void write(Data_out& out, PKT_ID const& value) const override;

    void read(Data_in& in, ConnectionInfo& value) const override;
    void write(Data_out& out, ConnectionInfo const& value) const override;
};
