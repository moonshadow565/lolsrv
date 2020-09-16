#include "proto.hpp"

#include "proto/proto_0.8.13.26.hpp"
#include "proto/proto_0.9.22.14.hpp"
#include "proto/proto_0.9.22.14_ab.hpp"
#include "proto/proto_0.9.22.16.hpp"
#include "proto/proto_0.9.22.18.hpp"
#include "proto/proto_0.9.25.21.hpp"
#include "proto/proto_0.9.25.24.hpp"
#include "proto/proto_0.9.25.36.hpp"
#include "proto/proto_1.0.0.100.hpp"
#include "proto/proto_1.0.0.101.hpp"
#include "proto/proto_1.0.0.102.hpp"
#include "proto/proto_1.0.0.103.hpp"
#include "proto/proto_1.0.0.104.hpp"
#include "proto/proto_1.0.0.105.hpp"
#include "proto/proto_1.0.0.106.hpp"
#include "proto/proto_1.0.0.107.hpp"
#include "proto/proto_1.0.0.108.hpp"
#include "proto/proto_1.0.0.109.hpp"
#include "proto/proto_1.0.0.110.hpp"
#include "proto/proto_1.0.0.111.hpp"
#include "proto/proto_1.0.0.112.hpp"
#include "proto/proto_1.0.0.113.hpp"
#include "proto/proto_1.0.0.114.hpp"
#include "proto/proto_1.0.0.116.hpp"
#include "proto/proto_1.0.0.117.hpp"
#include "proto/proto_1.0.0.118.hpp"
#include "proto/proto_1.0.0.119.hpp"
#include "proto/proto_1.0.0.120.hpp"
#include "proto/proto_1.0.0.121.hpp"
#include "proto/proto_1.0.0.122.hpp"
#include "proto/proto_1.0.0.123.hpp"
#include "proto/proto_1.0.0.124.hpp"
#include "proto/proto_1.0.0.125.hpp"
#include "proto/proto_1.0.0.126.hpp"
#include "proto/proto_1.0.0.126_ab.hpp"
#include "proto/proto_1.0.0.127.hpp"
#include "proto/proto_1.0.0.128.hpp"
#include "proto/proto_1.0.0.129.hpp"
#include "proto/proto_1.0.0.130.hpp"
#include "proto/proto_1.0.0.131.hpp"
#include "proto/proto_1.0.0.25.hpp"
#include "proto/proto_1.0.0.28.hpp"
#include "proto/proto_1.0.0.52.hpp"
#include "proto/proto_1.0.0.58.hpp"
#include "proto/proto_1.0.0.61.hpp"
#include "proto/proto_1.0.0.63.hpp"
#include "proto/proto_1.0.0.66.hpp"
#include "proto/proto_1.0.0.70.hpp"
#include "proto/proto_1.0.0.72.hpp"
#include "proto/proto_1.0.0.74.hpp"
#include "proto/proto_1.0.0.75.hpp"
#include "proto/proto_1.0.0.79.hpp"
#include "proto/proto_1.0.0.81.hpp"
#include "proto/proto_1.0.0.82.hpp"
#include "proto/proto_1.0.0.83.hpp"
#include "proto/proto_1.0.0.85.hpp"
#include "proto/proto_1.0.0.86.hpp"
#include "proto/proto_1.0.0.87.hpp"
#include "proto/proto_1.0.0.94.hpp"
#include "proto/proto_1.0.0.96.hpp"
#include "proto/proto_1.0.0.97.hpp"
#include "proto/proto_1.0.0.98.hpp"
#include "proto/proto_1.0.0.99.hpp"

#include <algorithm>

Span<ProtoBase const*> proto_list() {
    static ProtoBase const* list[] = {
        new PROTO_VER(0.8.13.26), new PROTO_VER(0.9.22.14),    new PROTO_VER(0.9.22.14_ab), new PROTO_VER(0.9.22.16),
        new PROTO_VER(0.9.22.18), new PROTO_VER(0.9.25.21),    new PROTO_VER(0.9.25.24),    new PROTO_VER(0.9.25.36),
        new PROTO_VER(1.0.0.25),  new PROTO_VER(1.0.0.28),     new PROTO_VER(1.0.0.52),     new PROTO_VER(1.0.0.58),
        new PROTO_VER(1.0.0.61),  new PROTO_VER(1.0.0.63),     new PROTO_VER(1.0.0.66),     new PROTO_VER(1.0.0.70),
        new PROTO_VER(1.0.0.72),  new PROTO_VER(1.0.0.74),     new PROTO_VER(1.0.0.75),     new PROTO_VER(1.0.0.79),
        new PROTO_VER(1.0.0.81),  new PROTO_VER(1.0.0.82),     new PROTO_VER(1.0.0.83),     new PROTO_VER(1.0.0.85),
        new PROTO_VER(1.0.0.86),  new PROTO_VER(1.0.0.87),     new PROTO_VER(1.0.0.94),     new PROTO_VER(1.0.0.96),
        new PROTO_VER(1.0.0.97),  new PROTO_VER(1.0.0.98),     new PROTO_VER(1.0.0.99),     new PROTO_VER(1.0.0.100),
        new PROTO_VER(1.0.0.101), new PROTO_VER(1.0.0.102),    new PROTO_VER(1.0.0.103),    new PROTO_VER(1.0.0.104),
        new PROTO_VER(1.0.0.105), new PROTO_VER(1.0.0.106),    new PROTO_VER(1.0.0.107),    new PROTO_VER(1.0.0.108),
        new PROTO_VER(1.0.0.109), new PROTO_VER(1.0.0.110),    new PROTO_VER(1.0.0.111),    new PROTO_VER(1.0.0.112),
        new PROTO_VER(1.0.0.113), new PROTO_VER(1.0.0.114),    new PROTO_VER(1.0.0.116),    new PROTO_VER(1.0.0.117),
        new PROTO_VER(1.0.0.118), new PROTO_VER(1.0.0.119),    new PROTO_VER(1.0.0.120),    new PROTO_VER(1.0.0.121),
        new PROTO_VER(1.0.0.122), new PROTO_VER(1.0.0.123),    new PROTO_VER(1.0.0.124),    new PROTO_VER(1.0.0.125),
        new PROTO_VER(1.0.0.126), new PROTO_VER(1.0.0.126_ab), new PROTO_VER(1.0.0.127),    new PROTO_VER(1.0.0.128),
        new PROTO_VER(1.0.0.129), new PROTO_VER(1.0.0.130),    new PROTO_VER(1.0.0.131),
    };
    return list;
}

ProtoBase const* find_protocol(std::string_view name) {
    auto const list = proto_list();
    auto const i = std::find_if(list.begin(), list.end(), [name](auto const& p) { return name == p->name(); });
    return i != list.end() ? *i : nullptr;
}
