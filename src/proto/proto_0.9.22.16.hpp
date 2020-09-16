#pragma once
#include "proto_0.9.22.14.hpp"

IMPL_PROTO_VER(PROTO_VER(0.9.22.16), PROTO_VER(0.9.22.14)) {
public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;

    Span<ProtoNameID const> pkt_array() const override;
};
