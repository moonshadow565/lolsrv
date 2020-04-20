#pragma once
#include <array>
#include <inttypes.h>
#include <iosfwd>
#include <string>
#include <vector>

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;
using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
// using uint64 = uint64_t;
using vec2 = ::std::array<float, 2>;
using vec3 = ::std::array<float, 3>;
using vec4 = ::std::array<float, 4>;
using bytes = ::std::vector<uint8>;
using ssize = ::std::streamsize;
