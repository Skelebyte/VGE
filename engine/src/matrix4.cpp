#include "../matrix4.hpp"
#include "../mathf.hpp"

using namespace vge;

Matrix4::Matrix4() {
  for (int i = 0; i < 16; i++) {
    data[i] = 0;
  }
}

Matrix4 Matrix4::identity() {
  Matrix4 mat = Matrix4();

  mat.data[0] = 1;
  mat.data[5] = 1;
  mat.data[10] = 1;
  mat.data[15] = 1;

  return mat;
}

Matrix4 Matrix4::transformation(const Vector3 &position,
                                const Vector3 &rotation, const Vector3 &scale) {
  Matrix4 pos = identity();
  Matrix4 rot = identity();
  Matrix4 sca = identity();

  pos.setTranslation(position);
  rot.setRotation(rotation);
  sca.setScale(scale);

  return pos * rot * sca;
}

Matrix4 Matrix4::perspective(float fovDeg, float aspect, float near,
                             float far) {
  Matrix4 mat = identity();

  float rad = Mathf::toRadians(fovDeg);

  mat.data[0] = 1 / (aspect * tan(rad / 2));
  mat.data[5] = 1 / tan(rad / 2);
  mat.data[10] = -(far + near) / (far - near);
  mat.data[11] = -1;
  mat.data[14] = -(2 * far * near) / (far - near);
  mat.data[15] = 0;

  return mat;
}

void Matrix4::setTranslation(const Vector3 &point) {
  this->data[12] = point.x;
  this->data[13] = point.y;
  this->data[14] = point.z;
}

void Matrix4::setRotation(const Vector3 &angles) {
  Matrix4 xRot = identity(), yRot = identity(), zRot = identity();

  Vector3 anglesRad =
      Vector3(Mathf::toRadians(angles.x), Mathf::toRadians(angles.y),
              Mathf::toRadians(angles.z));

  xRot.data[5] = cos(anglesRad.x);
  xRot.data[6] = -sin(anglesRad.x);
  xRot.data[9] = sin(anglesRad.x);
  xRot.data[10] = cos(anglesRad.x);
  yRot.data[0] = cos(anglesRad.y);
  yRot.data[2] = -sin(anglesRad.y);
  yRot.data[8] = sin(anglesRad.y);
  yRot.data[10] = cos(anglesRad.y);
  zRot.data[0] = cos(anglesRad.z);
  zRot.data[1] = sin(anglesRad.z);
  zRot.data[4] = -sin(anglesRad.z);
  zRot.data[5] = cos(anglesRad.z);

  *this = xRot * yRot * zRot;
}

void Matrix4::setScale(const Vector3 &scale) {
  this->data[0] = scale.x;
  this->data[5] = scale.y;
  this->data[10] = scale.z;
}

void Matrix4::lookAt(const Vector3 &target, const Vector3 &position,
                     const Vector3 &forward) {
  *this = identity();
  Vector3 forward_ = (position - target).normalized();
  Vector3 right =
      Vector3::cross(Vector3(0.0f, 1.0f, 0.0f), forward_).normalized();
  Vector3 up = Vector3::cross(forward_, right);

  this->data[0] = right.x;
  this->data[4] = right.y;
  this->data[8] = right.z;
  this->data[12] = -Vector3::dot(right, position);
  this->data[1] = up.x;
  this->data[5] = up.y;
  this->data[9] = up.z;
  this->data[13] = -Vector3::dot(up, position);
  this->data[2] = forward_.x;
  this->data[6] = forward_.y;
  this->data[10] = forward_.z;
  this->data[14] = -Vector3::dot(forward_, position);
}

Matrix4 Matrix4::operator*(const Matrix4 &other) {
  Matrix4 out = Matrix4();

  for (int col = 0; col < 4; col++) {
    for (int row = 0; row < 4; row++) {
      float sum = 0.0f;
      for (int i = 0; i < 4; i++) {
        sum += this->data[i * 4 + row] * other.data[col * 4 + i];
      }
      out.data[col * 4 + row] = sum;
    }
  }
  return out;
}

void Matrix4::operator=(const Matrix4 &other) {
  for (int i = 0; i < 16; i++) {
    this->data[i] = other.data[i];
  }
}