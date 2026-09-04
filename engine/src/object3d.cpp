#include "../inc/object3d.hpp"

using namespace vge;

/* ------------ Transform3D ------------ */

Transform3D::Transform3D(const Vector3 &pos, const Vector3 &rotEul,
                         const Vector3 &scl) {
  position = pos;
  rotationEuler = rotEul;
  scale = scl;
}

bool Transform3D::Process() { return true; }

// TODO: finish
Vector3 Transform3D::Forward() const { return Vector3(); }

/* ------------ Object3D ------------ */

Object3D::Object3D() {
  children = List<Object3D>();
  transform = Transform3D();
  enabled = true;
}

Object3D::~Object3D() {}

bool Object3D::Process() {
  if (!enabled)
    return false;

  transform.Process();

  return true;
}

/* ------------ Camera ------------ */

Camera::Camera(float fovDeg, float near, float far) : Object3D() {
  fov = fovDeg;
  this->near = near;
  this->far = far;

  // view = Matrix4x4(true);
  // perspective = Matrix4x4(true);

  current = true;
}

Camera::~Camera() {}

bool Camera::Process() {
  if (!Object3D::Process())
    return false;

  // view.LookAt(transform.position, transform.position + transform.Forward(),
  //             Vector3(0.0f, 1.0f, 0.0f));

  return true;
}
