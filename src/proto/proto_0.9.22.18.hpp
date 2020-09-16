#pragma once
#include "proto_0.9.22.16.hpp"

IMPL_PROTO_VER(PROTO_VER(0.9.22.18), PROTO_VER(0.9.22.16)) {
public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;
};
