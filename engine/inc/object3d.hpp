#ifndef VGE_OBJECT3D_HPP
#define VGE_OBJECT3D_HPP

#include "common.hpp"
#include "list.hpp"
#include "logger.hpp"
#include "matrix.hpp"
#include "memory.hpp"
#include "vector3.hpp"
#include "window.hpp"

namespace vge {

struct Processable {
  virtual bool Process() = 0;
};

struct Transform3D : Processable {
  Transform3D(const Vector3 &pos = Vector3(0.0f),
              const Vector3 &rotEul = Vector3(0.0f),
              const Vector3 &scl = Vector3(1.0f));

  bool Process() override;
  Matrix &GetTransformationMatrix();
  Vector3 Right() const;
  Vector3 Up() const;
  Vector3 Forward() const;

  Vector3 position;
  /**
   * @brief Euler rotation in degrees
   */
  Vector3 rotation;
  Vector3 scale;

protected:
  Matrix transformation;
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
  Matrix view;
  Matrix projection;
  bool current;
};

} // namespace vge

#endif
