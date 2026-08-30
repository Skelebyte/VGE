#include "../inc/matrix4x4.hpp"
#include "../inc/mathf.hpp"
#include <cstring>

using namespace vge;

Matrix4x4::Matrix4x4(bool identity) {
  // data = Pointer<float>();
  data.Malloc(16);

  if (identity) {
    this->Identity();
  } else {
    for (int i = 0; i < 16; i++) {
      data[i] = 0;
    }
  }
}

// Matrix4x4::~Matrix4x4() { data.Free(); }

void Matrix4x4::Identity() {
  for (int i = 0; i < 16; i++) {
    data[i] = 0;
  }

  data[0] = 1;
  data[5] = 1;
  data[10] = 1;
  data[15] = 1;
}

Matrix4x4 Matrix4x4::Transformation(const Vector3 &position,
                                    const Vector3 &rotation,
                                    const Vector3 &scale) {
  Matrix4x4 pos = Matrix4x4(true), rot = Matrix4x4(true), sca = Matrix4x4(true);

  pos.SetTranslation(position);
  rot.SetRotation(rotation);
  sca.SetScale(scale);

  return pos * rot * sca;
}

Matrix4x4 Matrix4x4::Perspective(float fovDeg, float aspect, float near,
                                 float far) {
  Matrix4x4 mat = Matrix4x4(true);

  float rad = Mathf::ToRadians(fovDeg);

  mat.data[0] = 1 / (aspect * tan(rad / 2));
  mat.data[5] = 1 / tan(rad / 2);
  mat.data[10] = -(far + near) / (far - near);
  mat.data[11] = -1;
  mat.data[14] = -(2 * far * near) / (far - near);
  mat.data[15] = 0;

  return mat;
}

void Matrix4x4::SetTranslation(const Vector3 &point) {
  this->data[12] = point.x;
  this->data[13] = point.y;
  this->data[14] = point.z;
}

void Matrix4x4::SetRotation(const Vector3 &angles) {
  Matrix4x4 xRot = Matrix4x4(true), yRot = Matrix4x4(true),
            zRot = Matrix4x4(true);

  Vector3 anglesRad =
      Vector3(Mathf::ToRadians(angles.x), Mathf::ToRadians(angles.y),
              Mathf::ToRadians(angles.z));

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

void Matrix4x4::SetScale(const Vector3 &scale) {
  this->data[0] = scale.x;
  this->data[5] = scale.y;
  this->data[10] = scale.z;
}

void Matrix4x4::LookAt(const Vector3 &target, const Vector3 &position,
                       const Vector3 &forward) {
  this->Identity();
  Vector3 forward_ = (position - target).Normalized();
  Vector3 right =
      Vector3::Cross(Vector3(0.0f, 1.0f, 0.0f), forward_).Normalized();
  Vector3 up = Vector3::Cross(forward_, right);

  this->data[0] = right.x;
  this->data[4] = right.y;
  this->data[8] = right.z;
  this->data[12] = -Vector3::Dot(right, position);
  this->data[1] = up.x;
  this->data[5] = up.y;
  this->data[9] = up.z;
  this->data[13] = -Vector3::Dot(up, position);
  this->data[2] = forward_.x;
  this->data[6] = forward_.y;
  this->data[10] = forward_.z;
  this->data[14] = -Vector3::Dot(forward_, position);
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &other) {
  Matrix4x4 out = Matrix4x4();

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

void Matrix4x4::operator=(const Matrix4x4 &other) {
  for (int i = 0; i < 16; i++) {
    this->data[i] = other.data[i];
  }
}