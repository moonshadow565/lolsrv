#pragma once
#include "r3d.hpp"

#include <algorithm>
#include <cmath>
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

/// r3dPoint2D
inline constexpr bool operator==(r3dPoint2D const& left, r3dPoint2D const& right) noexcept {
    return left.x == right.x && left.y == right.y;
}
inline constexpr bool operator!=(r3dPoint2D const& left, r3dPoint2D const& right) noexcept { return !(left == right); }
inline constexpr r3dPoint2D operator+(r3dPoint2D const& left, r3dPoint2D const& right) noexcept {
    return r3dPoint2D{left.x + right.x, left.y + right.y};
}
inline constexpr r3dPoint2D operator-(r3dPoint2D const& left, r3dPoint2D const& right) noexcept {
    return r3dPoint2D{left.x - right.x, left.y - right.y};
}
inline constexpr r3dPoint2D operator*(r3dPoint2D const& left, r3dPoint2D const& right) noexcept {
    return r3dPoint2D{left.x * right.x, left.y * right.y};
}
inline constexpr r3dPoint2D operator/(r3dPoint2D const& left, r3dPoint2D const& right) noexcept {
    return r3dPoint2D{left.x / right.x, left.y / right.y};
}
inline constexpr r3dPoint2D operator+(r3dPoint2D const& left, float right) noexcept {
    return r3dPoint2D{left.x + right, left.y + right};
}
inline constexpr r3dPoint2D operator-(r3dPoint2D const& left, float right) noexcept {
    return r3dPoint2D{left.x - right, left.y - right};
}
inline constexpr r3dPoint2D operator*(r3dPoint2D const& left, float right) noexcept {
    return r3dPoint2D{left.x * right, left.y * right};
}
inline constexpr r3dPoint2D operator/(r3dPoint2D const& left, float right) noexcept {
    return r3dPoint2D{left.x / right, left.y / right};
}
inline constexpr r3dPoint2D operator+(float left, r3dPoint2D const& right) noexcept { return right + left; }
inline constexpr r3dPoint2D operator*(float left, r3dPoint2D const& right) noexcept { return right * left; }
inline constexpr r3dPoint2D operator+=(r3dPoint2D& left, r3dPoint2D const& right) noexcept {
    return left = left + right;
}
inline constexpr r3dPoint2D operator-=(r3dPoint2D& left, r3dPoint2D const& right) noexcept {
    return left = left - right;
}
inline constexpr r3dPoint2D operator*=(r3dPoint2D& left, r3dPoint2D const& right) noexcept {
    return left = left * right;
}
inline constexpr r3dPoint2D operator/=(r3dPoint2D& left, r3dPoint2D const& right) noexcept {
    return left = left / right;
}
inline constexpr r3dPoint2D operator+=(r3dPoint2D& left, float right) noexcept { return left = left + right; }
inline constexpr r3dPoint2D operator-=(r3dPoint2D& left, float right) noexcept { return left = left - right; }
inline constexpr r3dPoint2D operator*=(r3dPoint2D& left, float right) noexcept { return left = left * right; }
inline constexpr r3dPoint2D operator/=(r3dPoint2D& left, float right) noexcept { return left = left / right; }

/// r3dPoint3D
inline constexpr bool operator==(r3dPoint3D const& left, r3dPoint3D const& right) noexcept {
    return left.x == right.x && left.y == right.y && left.z == right.z;
}
inline constexpr bool operator!=(r3dPoint3D const& left, r3dPoint3D const& right) noexcept { return !(left == right); }
inline constexpr r3dPoint3D operator+(r3dPoint3D const& left, r3dPoint3D const& right) noexcept {
    return r3dPoint3D{left.x + right.x, left.y + right.y, left.z + right.z};
}
inline constexpr r3dPoint3D operator-(r3dPoint3D const& left, r3dPoint3D const& right) noexcept {
    return r3dPoint3D{left.x - right.x, left.y - right.y, left.z - right.z};
}
inline constexpr r3dPoint3D operator*(r3dPoint3D const& left, r3dPoint3D const& right) noexcept {
    return r3dPoint3D{left.x * right.x, left.y * right.y, left.z * right.z};
}
inline constexpr r3dPoint3D operator/(r3dPoint3D const& left, r3dPoint3D const& right) noexcept {
    return r3dPoint3D{left.x / right.x, left.y / right.y, left.z / right.z};
}
inline constexpr r3dPoint3D operator+(r3dPoint3D const& left, float right) noexcept {
    return r3dPoint3D{left.x + right, left.y + right, left.z + right};
}
inline constexpr r3dPoint3D operator-(r3dPoint3D const& left, float right) noexcept {
    return r3dPoint3D{left.x - right, left.y - right, left.z - right};
}
inline constexpr r3dPoint3D operator*(r3dPoint3D const& left, float right) noexcept {
    return r3dPoint3D{left.x * right, left.y * right, left.z * right};
}
inline constexpr r3dPoint3D operator/(r3dPoint3D const& left, float right) noexcept {
    return r3dPoint3D{left.x / right, left.y / right, left.z / right};
}
inline constexpr r3dPoint3D operator+(float left, r3dPoint3D const& right) noexcept { return right + left; }
inline constexpr r3dPoint3D operator*(float left, r3dPoint3D const& right) noexcept { return right * left; }
inline constexpr r3dPoint3D operator+=(r3dPoint3D& left, float right) noexcept { return left = left + right; }
inline constexpr r3dPoint3D operator-=(r3dPoint3D& left, float right) noexcept { return left = left - right; }
inline constexpr r3dPoint3D operator/=(r3dPoint3D& left, float right) noexcept { return left = left / right; }
inline constexpr r3dPoint3D operator*=(r3dPoint3D& left, float right) noexcept { return left = left * right; }
inline constexpr r3dPoint3D operator+=(r3dPoint3D& left, r3dPoint3D const& right) noexcept {
    return left = left + right;
}
inline constexpr r3dPoint3D operator-=(r3dPoint3D& left, r3dPoint3D const& right) noexcept {
    return left = left - right;
}
inline constexpr r3dPoint3D operator/=(r3dPoint3D& left, r3dPoint3D const& right) noexcept {
    return left = left / right;
}
inline constexpr r3dPoint3D operator*=(r3dPoint3D& left, r3dPoint3D const& right) noexcept {
    return left = left * right;
}

/// Math
inline constexpr float R3D_EPSILON = 0.00001f;

// Returns the Inverse Square Root of a number
inline float invSqrt(float value) noexcept { return 1.0f / std::sqrt(value); }
// Returns whether the specified r3dPoint2D is Null(Zero)
inline bool isNull(r3dPoint2D const& point) noexcept { return point.x == 0.0f && point.y == 0.0f; }
// Returns whether the specified r3dPoint3D is Null(Zero)
inline bool isNull(r3dPoint3D const& point) noexcept { return point.x == 0.0f && point.y == 0.0f && point.z == 0.0f; }
// R eturns the Dot Product of the specified Vectors
inline float dot(r3dPoint2D const& point, r3dPoint2D const& other) noexcept {
    return point.x * other.x + point.y * other.y;
}
// Returns the Dot Product of the specified Vectors
inline float dot(r3dPoint3D const& point, r3dPoint3D const& other) noexcept {
    return point.x * other.x + point.y * other.y + point.z * other.z;
}
// Returns the Squared Magnitude of the specified r3dPoint2D
inline float lengthSq(r3dPoint2D const& point) noexcept { return dot(point, point); }
// Returns the Squared Magnitude of the specified r3dPoint3D
inline float lengthSq(r3dPoint3D const& point) noexcept { return dot(point, point); }
// Returns the Magnitude of the specified r3dPoint2D
inline float length(r3dPoint2D const& point) noexcept { return sqrtf(lengthSq(point)); }
// Returns the Magnitude of the specified r3dPoint3D
inline float length(r3dPoint3D const& point) noexcept { return sqrtf(lengthSq(point)); }
// Normalizes the specified r3dPoint2D
inline r3dPoint2D normalize(r3dPoint2D const& point) noexcept {
    auto const inv = invSqrt(lengthSq(point));
    return inv > 0.0f ? r3dPoint2D{point.x * inv, point.y * inv} : point;
}
// Normalizes the specified r3dPoint3D
inline r3dPoint3D normalize(r3dPoint3D const& point) noexcept {
    auto const inv = invSqrt(lengthSq(point));
    return inv > 0.0f ? r3dPoint3D{point.x * inv, point.y * inv, point.z * inv} : point;
}
// Returns the smallest component of the specified r3dPoint2D
inline float minElement(r3dPoint2D const& point) noexcept { return std::min(point.x, point.y); }
// Returns the smallest component of the specified r3dPoint3D
inline float minElement(r3dPoint3D const& point) noexcept { return std::min(std::min(point.x, point.y), point.z); }
// Returns the biggest component of the specified r3dPoint2D
inline float maxElement(r3dPoint2D const& point) noexcept { return std::max(point.x, point.y); }
// Returns the biggest component of the specified r3dPoint3D
inline float maxElement(r3dPoint3D const& point) noexcept { return std::min(std::max(point.x, point.y), point.z); }
inline float angle(r3dPoint2D const& point, r3dPoint2D const& with) noexcept {
    return std::acos(std::clamp(dot(point, with), -1.0f, 1.0f));
}
inline float angle(r3dPoint3D const& point, r3dPoint3D const& with) noexcept {
    return std::acos(std::clamp(dot(point, with), -1.0f, 1.0f));
}
// Whether the specified Vectors are almost equal according to the comparer delta
inline bool almostEqual(r3dPoint2D const& point, r3dPoint2D const& other, float delta = R3D_EPSILON) noexcept {
    return std::abs(point.x - other.x) <= delta && std::abs(point.y - other.y) <= delta;
}
// Whether the specified Vectors are almost equal according to the comparer delta
inline bool almostEqual(r3dPoint3D const& point, r3dPoint3D const& other, float delta = R3D_EPSILON) noexcept {
    return std::abs(point.x - other.x) <= delta && std::abs(point.y - other.y) <= delta &&
           std::abs(point.z - other.z) <= delta;
}
// Returns the Cross Product of the specified Vectors
inline r3dPoint3D cross(r3dPoint3D const& point, r3dPoint3D const& other) noexcept {
    return r3dPoint3D{point.y * other.z - point.z * other.y,
                      point.z * other.x - point.x * other.z,
                      point.x * other.y - point.y * other.x};
}
// Rotates the specified Vector about the specified origin Vector using the specified angle
inline r3dPoint3D rotateX(r3dPoint3D const& point, float angle, r3dPoint3D const& about = {}) noexcept {
    if (angle) {
        auto const y = point.y - about.y;
        auto const z = point.z - about.z;
        if (y || z) {
            return r3dPoint3D{point.x,
                              y * std::cos(angle) - z * std::sin(angle) + about.y,
                              z * std::cos(angle) + y * std::sin(angle) + about.z};
        }
    }
    return point;
}
// Rotates the specified Vector about the specified origin Vector by the specified angle
inline r3dPoint3D rotateY(r3dPoint3D const& point, float angle, r3dPoint3D const& about = {}) noexcept {
    if (angle) {
        auto const x = point.x - about.x;
        auto const z = point.z - about.z;
        if (x || z) {
            return r3dPoint3D{x * std::cos(angle) + z * std::sin(angle) + about.x,
                              point.y,
                              z * std::cos(angle) - x * std::sin(angle) + about.z};
        }
    }
    return point;
}
// Rotates the specified Vector about the specified origin Vector by the specified angle
inline r3dPoint3D rotateZ(r3dPoint3D const& point, float angle, r3dPoint3D const& about = {}) noexcept {
    if (angle) {
        auto const x = point.x - about.x;
        auto const y = point.y - about.y;
        if (x || y) {
            return r3dPoint3D{x * std::sin(angle) - y * std::cos(angle) + about.x,
                              y * std::sin(angle) + x * std::cos(angle) + about.y,
                              point.z};
        }
    }
    return point;
}
// Rotates the specified Vector by the specified angle
inline r3dPoint2D Rotate(r3dPoint2D const& point, float angle) noexcept {
    return r3dPoint2D{point.x * std::cos(angle) - point.y * std::sin(angle),
                      point.x * std::sin(angle) + point.y * std::cos(angle)};
}
