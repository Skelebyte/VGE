#ifndef VGE_VECTOR2_HPP
#define VGE_VECTOR2_HPP

#include "common.hpp"
#include "logger.hpp"
#include "memory.hpp"

namespace vge {

union Vector2 {
  struct {
    float x, y;
  };
  float data[2];

  Vector2(float xy = 0.0f);
  Vector2(float x, float y);
  ~Vector2();

  static float Dot(const Vector2 &a, const Vector2 &b);

  float Length() const;
  Vector2 Normalized() const;

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