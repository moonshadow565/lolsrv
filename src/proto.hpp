#pragma once
#include "proto_base.hpp"

#include <span.hpp>

extern Span<ProtoBase const*> proto_list();

extern ProtoBase const* find_protocol(std::string_view name);
