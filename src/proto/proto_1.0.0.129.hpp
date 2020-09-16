#pragma once
#include "proto_1.0.0.128.hpp"

IMPL_PROTO_VER(PROTO_VER(1.0.0.129), PROTO_VER(1.0.0.128)) {
public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;
};
