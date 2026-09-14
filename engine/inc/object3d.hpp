#ifndef VGE_OBJECT3D_HPP
#define VGE_OBJECT3D_HPP

#include "asset.hpp"
#include "common.hpp"
#include "list.hpp"
#include "logger.hpp"
#include "memory.hpp"
#include "window.hpp"

namespace vge {

struct Processable {
  virtual bool Process() = 0;
};

struct Transform3D : Processable {
  Transform3D(const Vector3f &pos = Vector3f(0.0f),
              const Vector3f &rotEul = Vector3f(0.0f),
              const Vector3f &scl = Vector3f(1.0f));

  bool Process() override;
  Matrix<4, 4> &GetTransformationMatrix();
  Vector3f Right() const;
  Vector3f Up() const;
  Vector3f Forward() const;

  Vector3f position;
  /**
   * @brief Euler rotation in degrees
   */
  Vector3f rotation;
  Vector3f scale;

protected:
  Matrix<4, 4> transformation;
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
  Matrix<4, 4> view;
  Matrix<4, 4> projection;
  bool current;
};

enum struct PrimitiveMesh { PLANE = 0, CUBE = 1, SPHERE = 2 };

struct MeshRenderer : Object3D {
  MeshRenderer(const PrimitiveMesh &primitive = PrimitiveMesh::PLANE);
  MeshRenderer(const String &path);

  Texture diffuse;
  Mesh mesh;
};

} // namespace vge

#endif
