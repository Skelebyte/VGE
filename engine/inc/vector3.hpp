#ifndef VGE_VECTOR3_HPP
#define VGE_VECTOR3_HPP

#include "common.hpp"
#include "logger.hpp"

namespace vge {

struct Vector3 {
  float x, y, z;

  Vector3(float xyz = 0.0f);
  Vector3(float x, float y, float z);

  static Vector3 cross(const Vector3 &a, const Vector3 &b);
  static float dot(const Vector3 &a, const Vector3 &b);

  float length() const;
  Vector3 normalized() const;

  Vector3 operator+(const Vector3 &other) const;
  Vector3 operator-(const Vector3 &other) const;
  Vector3 operator*(const Vector3 &other) const;
  Vector3 operator*(const float &other) const;
  void operator=(const Vector3 &other);
  void operator+=(const Vector3 &other);
  void operator-=(const Vector3 &other);
  bool operator==(const Vector3 &other) const;
};

} // namespace vge

#endif