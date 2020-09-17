#pragma once
#include "proto_1.0.0.86.hpp"

IMPL_PROTO_VER(PROTO_VER(1.0.0.87), PROTO_VER(1.0.0.86)) {
public:
    using ProtoBase::read;
    using ProtoBase::write;

    std::string_view name() const override;

    void read(Data_in & io, PKT_SpawnMinionS2C & value) const override;
    void write(Data_out & io, PKT_SpawnMinionS2C const& value) const override;
};
