#pragma once
#include "types.hpp"

struct Point2D
{
  Point2D(const vec2& v) : x(v[0]), y(v[1]) {}
  Point2D(float a, float b) : x(a), y(b) {}
  Point2D() : x(0), y(0) {}
  float x, y;
};
inline bool operator==(const Point2D& left, const Point2D& right)
{
  return left.x == right.x && left.y == right.y;
}
 inline bool operator!=(const Point2D& left, const Point2D& right)
{
  return !(left == right);
}
 inline Point2D operator+(const Point2D& left, const Point2D& right)
{
  return Point2D{left.x + right.x, left.y + right.y};
}
 inline Point2D operator-(const Point2D& left, const Point2D& right)
{
  return Point2D{left.x - right.x, left.y - right.y};
}
 inline Point2D operator*(const Point2D& left, const Point2D& right)
{
  return Point2D{left.x * right.x, left.y * right.y};
}
 inline Point2D operator/(const Point2D& left, const Point2D& right)
{
  return Point2D{left.x / right.x, left.y / right.y};
}
 inline Point2D operator+(const Point2D& left, float right)
{
  return Point2D{left.x + right, left.y + right};
}
 inline Point2D operator-(const Point2D& left, float right)
{
  return Point2D{left.x - right, left.y - right};
}
 inline Point2D operator*(const Point2D& left, float right)
{
  return Point2D{left.x * right, left.y * right};
}
 inline Point2D operator/(const Point2D& left, float right)
{
  return Point2D{left.x / right, left.y / right};
}
 inline Point2D operator+(float left, const Point2D& right)
{
  return right + left;
}
 inline Point2D operator*(float left, const Point2D& right)
{
  return right * left;
}
 inline Point2D operator+=(Point2D& left, const Point2D& right)
{
  return left = left + right;
}
 inline Point2D operator-=(Point2D& left, const Point2D& right)
{
  return left = left - right;
}
 inline Point2D operator*=(Point2D& left, const Point2D& right)
{
  return left = left * right;
}
 inline Point2D operator/=(Point2D& left, const Point2D& right)
{
  return left = left / right;
}
 inline Point2D operator+=(Point2D& left, float right)
{
  return left = left + right;
}
 inline Point2D operator-=(Point2D& left, float right)
{
  return left = left - right;
}
 inline Point2D operator*=(Point2D& left, float right)
{
  return left = left * right;
}
 inline Point2D operator/=(Point2D& left, float right)
{
  return left = left / right;
}
