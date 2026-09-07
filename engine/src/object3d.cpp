#include "../inc/object3d.hpp"

using namespace vge;

/* ------------ Transform3D ------------ */

Transform3D::Transform3D(const Vector3 &pos, const Vector3 &rotEul,
                         const Vector3 &scl)
    : position(pos), rotation(rotEul), scale(scl), transformation(4, true) {

  transformation.Transform(position, rotation, scale);
}

bool Transform3D::Process() {
  transformation.Transform(position, rotation, scale);
  return true;
}

Matrix &Transform3D::GetTransformationMatrix() { return transformation; }

Vector3 Transform3D::Right() const {
  return Vector3(transformation.GetEntry(0, 0), transformation.GetEntry(0, 1),
                 transformation.GetEntry(0, 2));
}
Vector3 Transform3D::Up() const {
  return Vector3(transformation.GetEntry(2, 0), transformation.GetEntry(2, 1),
                 transformation.GetEntry(2, 2));
}
Vector3 Transform3D::Forward() const {
  return Vector3(transformation.GetEntry(1, 0), transformation.GetEntry(1, 1),
                 transformation.GetEntry(1, 2));
}

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

Camera::Camera(float fovDeg, float near, float far)
    : Object3D(), view(4), projection(4) {
  fov = fovDeg;
  this->near = near;
  this->far = far;

  current = true;
}

Camera::~Camera() {}

bool Camera::Process() {
  if (!Object3D::Process())
    return false;

  view.LookAt(transform.position, transform.position + transform.Forward(),
              Vector3(0.0f, 1.0f, 0.0f));

  projection.Perspective(fov, Window::GetViewportAspect(), near, far);

  return true;
}
