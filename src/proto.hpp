#pragma once
#include <span.hpp>
#include "proto/proto_base.hpp"

extern Span<ProtoBase const*> proto_list();

extern ProtoBase const* find_protocol(std::string_view name);
