#ifndef VGE_OBJECT3D_HPP
#define VGE_OBJECT3D_HPP

#include "common.hpp"
#include "list.hpp"
#include "logger.hpp"
// #include "matrix4x4.hpp"
#include "memory.hpp"
#include "vector3.hpp"

namespace vge {

struct Processable {
  virtual bool Process() = 0;
};

struct Transform3D : Processable {
  Transform3D(const Vector3 &pos = Vector3(0.0f),
              const Vector3 &rotEul = Vector3(0.0f),
              const Vector3 &scl = Vector3(1.0f));

  bool Process() override;
  Vector3 Forward() const;

  Vector3 position;
  Vector3 rotationEuler;
  Vector3 scale;
};

struct Object3D : Processable {
  Object3D();
  ~Object3D();

  bool Process() override;

  Transform3D transform;
  List<Object3D> children;
  bool enabled;
};

struct Camera : Object3D {
  Camera(float fovDeg = 75.0f, float near = 0.001f, float far = 1000.0f);
  ~Camera();

  bool Process() override;

  /**
   * @brief Field of view in degrees.
   *
   */
  float fov;
  float near;
  float far;
  // Matrix4x4 view;
  // Matrix4x4 perspective;
  bool current;

protected:
};

} // namespace vge

#endif
