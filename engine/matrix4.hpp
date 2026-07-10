#ifndef VGE_MATRIX4_HPP
#define VGE_MATRIX4_HPP

#include "common.hpp"
#include "logger.hpp"
#include "vector3.hpp"

namespace vge {
struct Matrix4 {
  float data[16] = {0};

  Matrix4();

  static Matrix4 identity();
  static Matrix4 transformation(const Vector3 &position,
                                const Vector3 &rotation, const Vector3 &scale);
  static Matrix4 perspective(float fovDeg, float aspect, float near, float far);

  void setTranslation(const Vector3 &point);
  void setRotation(const Vector3 &angles);
  void setScale(const Vector3 &scale);
  void lookAt(const Vector3 &target, const Vector3 &position,
              const Vector3 &forward);

  Matrix4 operator*(const Matrix4 &other);
  void operator=(const Matrix4 &other);
};
} // namespace vge

#endif