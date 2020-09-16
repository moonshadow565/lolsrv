#pragma once
#if __has_include(<span>)
#include <span>
template <typename T>
using Span = std::span<T>;
#else
// FIXME: older compilers
#endif
