#pragma once
#include "proto_1.0.0.114.hpp"

IMPL_PROTO_VER(PROTO_VER(1.0.0.116), PROTO_VER(1.0.0.114)) {
public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;
};
