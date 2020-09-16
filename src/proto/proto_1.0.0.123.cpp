#include "proto_1.0.0.123.hpp"

using ProtoVer = PROTO_VER(1.0.0.123);

std::string_view ProtoVer::name() const { return "1.0.0.123"; }

void ProtoVer::read(Data_in& io, PKT_C2S_MapPing& value) const {
    io.num<uint32_t>(value.fromID);
    io.point3d(value.pos);
    io.num<uint32_t>(value.target);
    io.bit<uint8_t>(field<uint8_t, 4>(value.pingCategory));
}
void ProtoVer::write(Data_out& io, PKT_C2S_MapPing const& value) const {
    io.num<uint32_t>(value.fromID);
    io.point3d(value.pos);
    io.num<uint32_t>(value.target);
    io.bit<uint8_t>(field<uint8_t, 4>(value.pingCategory));
}

void ProtoVer::read(Data_in& io, PKT_S2C_MapPing& value) const {
    io.num<uint32_t>(value.fromID);
    io.point3d(value.pos);
    io.num<uint32_t>(value.target);
    io.num<uint32_t>(value.src);
    io.bit<uint8_t>(field<uint8_t, 4>(value.pingCategory),
                    field<uint8_t, 1>(value.bPlayAudio),
                    field<uint8_t, 1>(value.bShowChat),
                    field<uint8_t, 1>(value.bPingThrottled));
}
void ProtoVer::write(Data_out& io, PKT_S2C_MapPing const& value) const {
    io.num<uint32_t>(value.fromID);
    io.point3d(value.pos);
    io.num<uint32_t>(value.target);
    io.num<uint32_t>(value.src);
    io.bit<uint8_t>(field<uint8_t, 4>(value.pingCategory),
                    field<uint8_t, 1>(value.bPlayAudio),
                    field<uint8_t, 1>(value.bShowChat),
                    field<uint8_t, 1>(value.bPingThrottled));
}
