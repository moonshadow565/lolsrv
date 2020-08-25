#pragma once
#include "proto_0.9.25.24.hpp"

IMPL_PROTO_VER(PROTO_VER(0.9.25.36), PROTO_VER(0.9.25.24)) {
    public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;
};
