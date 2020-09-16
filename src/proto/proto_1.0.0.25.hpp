#pragma once
#include "proto_0.9.25.36.hpp"

IMPL_PROTO_VER(PROTO_VER(1.0.0.25), PROTO_VER(0.9.25.36)) {
public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;

    Span<ProtoNameID const> pkt_array() const override;
};
