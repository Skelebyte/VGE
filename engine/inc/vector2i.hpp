#ifndef VGE_VECTOR2I_HPP
#define VGE_VECTOR2I_HPP

#include "common.hpp"
#include "logger.hpp"
// #include "memory.hpp"

namespace vge {

union Vector2I {
  struct {
    int32 x, y;
  };
  int32 data[2];

  Vector2I() = default;
  Vector2I(int xy);
  Vector2I(int x, int y);
  ~Vector2I();

  static float Dot(const Vector2I &a, const Vector2I &b);

  float Length() const;
  Vector2I Normalized() const;
  Vector2I Abs() const;
  String AsString() const;

  Vector2I operator+(const Vector2I &other) const;
  Vector2I operator-(const Vector2I &other) const;
  Vector2I operator*(const Vector2I &other) const;
  Vector2I operator*(const float &other) const;
  void operator=(const Vector2I &other);
  void operator+=(const Vector2I &other);
  void operator-=(const Vector2I &other);
  bool operator==(const Vector2I &other) const;
};

} // namespace vge

#endif