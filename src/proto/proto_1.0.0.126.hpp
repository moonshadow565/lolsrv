#pragma once
#include "proto_1.0.0.125.hpp"

IMPL_PROTO_VER(PROTO_VER(1.0.0.126), PROTO_VER(1.0.0.125)) {
    public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;

    Span<ProtoNameID const> pkt_array() const override;
};
