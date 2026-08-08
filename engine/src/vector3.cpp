#include "../inc/vector3.hpp"
#include "../inc/mathf.hpp"

using namespace vge;

Vector3::Vector3(float xyz) {
  x = xyz;
  y = xyz;
  z = xyz;
}

Vector3::Vector3(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector3 Vector3::cross(const Vector3 &a, const Vector3 &b) {
  return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                 a.x * b.y - a.y * b.x);
}

float Vector3::dot(const Vector3 &a, const Vector3 &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

float Vector3::length() const { return sqrt(x * x + y * y + z * z); }

Vector3 Vector3::normalized() const {
  Vector3 norm = *this;
  float len = this->length();

  norm.x /= len;
  norm.y /= len;
  norm.z /= len;

  return norm;
}

Vector3 Vector3::operator+(const Vector3 &other) const {
  return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3 &other) const {
  return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(const Vector3 &other) const {
  return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator*(const float &other) const {
  return Vector3(x * other, y * other, z * other);
}

void Vector3::operator=(const Vector3 &other) {
  x = other.x;
  x = other.x;
  x = other.x;
}

void Vector3::operator+=(const Vector3 &other) {
  x += other.x;
  y += other.y;
  z += other.z;
}

void Vector3::operator-=(const Vector3 &other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
}

bool Vector3::operator==(const Vector3 &other) const {
  return (x == other.x && y == other.y && z == other.z);
}