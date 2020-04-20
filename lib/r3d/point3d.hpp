#pragma once
#include "types.hpp"

struct Point3D
{
  Point3D(const vec3& v) : x(v[0]), y(v[1]), z(v[2]) {}
  Point3D(float a, float b, float c) : x(a), y(b), z(c) {}
  Point3D() : x(0), y(0), z(0) {}
  float x, y, z;
};
inline bool operator==(const Point3D& left, const Point3D& right)
{
  return left.x == right.x && left.y == right.y && left.z == right.z;
}
 inline bool operator!=(const Point3D& left, const Point3D& right)
{
  return !(left == right);
}
 inline Point3D operator+(const Point3D& left, const Point3D& right)
{
  return Point3D{left.x + right.x, left.y + right.y, left.z + right.z};
}
 inline Point3D operator-(const Point3D& left, const Point3D& right)
{
  return Point3D{left.x - right.x, left.y - right.y, left.z - right.z};
}
 inline Point3D operator*(const Point3D& left, const Point3D& right)
{
  return Point3D{left.x * right.x, left.y * right.y, left.z * right.z};
}
 inline Point3D operator/(const Point3D& left, const Point3D& right)
{
  return Point3D{left.x / right.x, left.y / right.y, left.z / right.z};
}
 inline Point3D operator+(const Point3D& left, float right)
{
  return Point3D{left.x + right, left.y + right, left.z + right};
}
 inline Point3D operator-(const Point3D& left, float right)
{
  return Point3D{left.x - right, left.y - right, left.z - right};
}
 inline Point3D operator*(const Point3D& left, float right)
{
  return Point3D{left.x * right, left.y * right, left.z * right};
}
 inline Point3D operator/(const Point3D& left, float right)
{
  return Point3D{left.x / right, left.y / right, left.z / right};
}
 inline Point3D operator+(float left, const Point3D& right)
{
  return right + left;
}
 inline Point3D operator*(float left, const Point3D& right)
{
  return right * left;
}
 inline Point3D operator+=(Point3D& left, float right)
{
  return left = left + right;
}
 inline Point3D operator-=(Point3D& left, float right)
{
  return left = left - right;
}
 inline Point3D operator/=(Point3D& left, float right)
{
  return left = left / right;
}
 inline Point3D operator*=(Point3D& left, float right)
{
  return left = left * right;
}
 inline Point3D operator+=(Point3D& left, const Point3D& right)
{
  return left = left + right;
}
 inline Point3D operator-=(Point3D& left, const Point3D& right)
{
  return left = left - right;
}
 inline Point3D operator/=(Point3D& left, const Point3D& right)
{
  return left = left / right;
}
 inline Point3D operator*=(Point3D& left, const Point3D& right)
{
  return left = left * right;
}
