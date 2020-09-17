#include "proto_1.0.0.122.hpp"

using ProtoVer = PROTO_VER(1.0.0.122);

std::string_view ProtoVer::name() const { return "1.0.0.122"; }

void ProtoVer::read(Data_in& io, PKT_SpawnMinionS2C& value) const {
    io.num<uint32_t>(value.fromID);
    io.num<uint32_t>(value.netObjID);
    io.num<uint8_t>(value.netNodeID);
    io.point3d(value.Pos);
    io.num<int32_t>(value.skinID);
    io.num<uint32_t>(value.CloneID);
    io.bit<uint32_t>(field<uint32_t, 9>(value.TeamID));
    io.bit<uint8_t>(field<uint8_t, 1>(value.IgnoreCollision),
                    field<uint8_t, 1>(value.IsWard),
                    field<uint8_t, 1>(value.useBehaviorTreeAI));
    io.fstr(value.Name, 64);
    io.fstr(value.SkinName, 64);
}
void ProtoVer::write(Data_out& io, PKT_SpawnMinionS2C const& value) const {
    io.num<uint32_t>(value.fromID);
    io.num<uint32_t>(value.netObjID);
    io.num<uint8_t>(value.netNodeID);
    io.point3d(value.Pos);
    io.num<int32_t>(value.skinID);
    io.num<uint32_t>(value.CloneID);
    io.bit<uint32_t>(field<uint32_t, 9>(value.TeamID));
    io.bit<uint8_t>(field<uint8_t, 1>(value.IgnoreCollision),
                    field<uint8_t, 1>(value.IsWard),
                    field<uint8_t, 1>(value.useBehaviorTreeAI));
    io.fstr(value.Name, 64);
    io.fstr(value.SkinName, 64);
}
