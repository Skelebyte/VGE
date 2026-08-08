#ifndef VGE_VECTOR2_HPP
#define VGE_VECTOR2_HPP

#include "common.hpp"
#include "logger.hpp"

namespace vge {

struct Vector2 {
  float x, y;

  Vector2(float xy = 0.0f);
  Vector2(float x, float y);

  static float dot(const Vector2 &a, const Vector2 &b);

  float length() const;
  Vector2 normalized() const;

  Vector2 operator+(const Vector2 &other) const;
  Vector2 operator-(const Vector2 &other) const;
  Vector2 operator*(const Vector2 &other) const;
  Vector2 operator*(const float &other) const;
  void operator=(const Vector2 &other);
  void operator+=(const Vector2 &other);
  void operator-=(const Vector2 &other);
  bool operator==(const Vector2 &other) const;
};

} // namespace vge

#endif