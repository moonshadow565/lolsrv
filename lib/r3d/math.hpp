#pragma once
#include <algorithm>
#include <cmath>
#include "point2d.hpp"
#include "point3d.hpp"
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

constexpr static const float PI = 3.1415926f;
constexpr static const float EPSILON = 0.00001f;
 // Returns the Inverse Square Root of a number
inline float invSqrt(float value)
{
  return 1.0f / std::sqrt(value);
}
 // Returns whether the specified Point2D is Null(Zero)
inline bool isNull(const Point2D& point)
{
  return point.x == 0 && point.y == 0;
}
 // Returns whether the specified Point3D is Null(Zero)
inline bool isNull(const Point3D& point)
{
  return point.x == 0 && point.y == 0 && point.z == 0;
}
 // R eturns the Dot Product of the specified Vectors
inline float dot(const Point2D& point, const Point2D& other)
{
  return point.x * other.x + point.y * other.y;
}
 // Returns the Dot Product of the specified Vectors
inline float dot(const Point3D& point, const Point3D& other)
{
  return point.x * other.x + point.y * other.y + point.z * other.z;
}
 // Returns the Squared Magnitude of the specified Point2D
inline float lengthSq(const Point2D& point)
{
  return dot(point, point);
}
 // Returns the Squared Magnitude of the specified Point3D
inline float lengthSq(const Point3D& point)
{
  return dot(point, point);
}
 // Returns the Magnitude of the specified Point2D
inline float length(const Point2D& point)
{
  return sqrtf(lengthSq(point));
}
 // Returns the Magnitude of the specified Point3D
inline float length(const Point3D& point)
{
  return sqrtf(lengthSq(point));
}
 // Normalizes the specified Point2D
inline Point2D normalize(const Point2D& point)
{
  float inv = invSqrt(lengthSq(point));
  return inv > 0 ? Point2D{point.x * inv, point.y * inv} : point;
}
 // Normalizes the specified Point3D
inline Point3D normalize(const Point3D& point)
{
  float inv = invSqrt(lengthSq(point));
  return inv > 0 ? Point3D{point.x * inv, point.y * inv, point.z * inv} : point;
}
 // Returns the smallest component of the specified Point2D
inline float minElement(const Point2D& point)
{
  return std::min(point.x, point.y);
}
 // Returns the smallest component of the specified Point3D
inline float minElement(const Point3D& point)
{
  return std::min(std::min(point.x, point.y), point.z);
}
 // Returns the biggest component of the specified Point2D
inline float maxElement(const Point2D& point)
{
  return std::max(point.x, point.y);
}
 // Returns the biggest component of the specified Point3D
inline float maxElement(const Point3D& point)
{
  return std::min(std::max(point.x, point.y), point.z);
}
 inline float angle(const Point2D& point, const Point2D& with)
{
  return std::acos(std::clamp(dot(point, with), -1.0f, 1.0f));
}
inline float angle(const Point3D& point, const Point3D& with)
{
  return std::acos(std::clamp(dot(point, with), -1.0f, 1.0f));
}
 // Whether the specified Vectors are almost equal according to the comparer delta
inline bool almostEqual(const Point2D& point, const Point2D& other, float delta = EPSILON)
{
  return std::abs(point.x - other.x) <= delta && std::abs(point.y - other.y) <= delta;
}
 // Whether the specified Vectors are almost equal according to the comparer delta
inline bool almostEqual(const Point3D& point, const Point3D& other, float delta = EPSILON)
{
  return std::abs(point.x - other.x) <= delta && std::abs(point.y - other.y) <= delta &&
         std::abs(point.z - other.z) <= delta;
}
 // Returns the Cross Product of the specified Vectors
inline Point3D cross(const Point3D& point, const Point3D& other)
{
  return Point3D{point.y * other.z - point.z * other.y,
                 point.z * other.x - point.x * other.z,
                 point.x * other.y - point.y * other.x};
}
 // Rotates the specified Vector about the specified origin Vector using the specified angle
inline Point3D rotateX(const Point3D& point, float angle, const Point3D& about = {})
{
  if (!angle)
    return point;
  auto y = point.y - about.y;
  auto z = point.z - about.z;
  if (!y && !z)
    return point;
  return Point3D{point.x,
                 y * std::cos(angle) - z * std::sin(angle) + about.y,
                 z * std::cos(angle) + y * std::sin(angle) + about.z};
}
 // Rotates the specified Vector about the specified origin Vector by the specified angle
inline Point3D rotateY(const Point3D& point, float angle, const Point3D& about = {})
{
  if (!angle)
    return point;
  auto x = point.x - about.x;
  auto z = point.z - about.z;
  if (!x && !z)
    return point;
  return Point3D{x * std::cos(angle) + z * std::sin(angle) + about.x,
                 point.y,
                 z * std::cos(angle) - x * std::sin(angle) + about.z};
}
 // Rotates the specified Vector about the specified origin Vector by the specified angle
inline Point3D rotateZ(const Point3D& point, float angle, const Point3D& about = {})
{
  if (!angle)
    return point;
  auto x = point.x - about.x;
  auto y = point.y - about.y;
  if (!x && !y)
    return point;
  return Point3D{x * std::sin(angle) - y * std::cos(angle) + about.x,
                 y * std::sin(angle) + x * std::cos(angle) + about.y,
                 point.z};
}
 // Rotates the specified Vector by the specified angle
inline Point2D Rotate(const Point2D& point, float angle)
{
  return Point2D{point.x * std::cos(angle) - point.y * std::sin(angle),
                 point.x * std::sin(angle) + point.y * std::cos(angle)};
}
