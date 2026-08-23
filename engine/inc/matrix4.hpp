#ifndef VGE_MATRIX4_HPP
#define VGE_MATRIX4_HPP

#include "common.hpp"
#include "logger.hpp"
#include "memory.hpp"
#include "vector3.hpp"

namespace vge {
struct Matrix4 {

  Matrix4(bool identity = false);
  ~Matrix4();

  // float data[16] = {0};
  Pointer<float> data;

  void Identity();
  static Matrix4 Transformation(const Vector3 &position,
                                const Vector3 &rotation, const Vector3 &scale);
  static Matrix4 Perspective(float fovDeg, float aspect, float near, float far);

  void SetTranslation(const Vector3 &point);
  void SetRotation(const Vector3 &angles);
  void SetScale(const Vector3 &scale);
  void LookAt(const Vector3 &target, const Vector3 &position,
              const Vector3 &forward);

  Matrix4 operator*(const Matrix4 &other);
  void operator=(const Matrix4 &other);
};
} // namespace vge

#endif