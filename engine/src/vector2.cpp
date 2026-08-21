#include "../inc/vector2.hpp"
#include "../inc/mathf.hpp"

using namespace vge;

Vector2::Vector2(float xy) {
  x = xy;
  y = xy;
}

Vector2::Vector2(float x, float y) {
  this->x = x;
  this->y = y;
}

Vector2::~Vector2() {}

float Vector2::Dot(const Vector2 &a, const Vector2 &b) {
  return a.x * b.x + a.y * b.y;
}

float Vector2::Length() const { return sqrt(x * x + y * y); }

Vector2 Vector2::Normalized() const {
  Vector2 norm = *this;
  float len = this->Length();

  norm.x /= len;
  norm.y /= len;

  return norm;
}

Vector2 Vector2::operator+(const Vector2 &other) const {
  return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2 &other) const {
  return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(const Vector2 &other) const {
  return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::operator*(const float &other) const {
  return Vector2(x * other, y * other);
}

void Vector2::operator=(const Vector2 &other) {
  x = other.x;
  x = other.x;
}

void Vector2::operator+=(const Vector2 &other) {
  x += other.x;
  y += other.y;
}

void Vector2::operator-=(const Vector2 &other) {
  x -= other.x;
  y -= other.y;
}

bool Vector2::operator==(const Vector2 &other) const {
  return (x == other.x && y == other.y);
}