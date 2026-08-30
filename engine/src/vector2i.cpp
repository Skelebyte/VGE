#include "../inc/vector2i.hpp"
#include "../inc/mathf.hpp"

using namespace vge;

Vector2I::Vector2I(int32 xy) {

  x = xy;
  y = xy;
}

Vector2I::Vector2I(int32 x, int32 y) {
  this->x = x;
  this->y = y;
}

Vector2I::~Vector2I() {}

float Vector2I::Dot(const Vector2I &a, const Vector2I &b) {
  return a.x * b.x + a.y * b.y;
}

float Vector2I::Length() const { return sqrt(x * x + y * y); }

Vector2I Vector2I::Normalized() const {
  Vector2I norm = *this;
  float len = this->Length();

  norm.x /= len;
  norm.y /= len;

  return norm;
}

Vector2I Vector2I::Abs() const {
  return Vector2I(Mathf::Abs(x), Mathf::Abs(y));
}

String Vector2I::AsString() const {
  return "(" + ToString(x) + ", " + ToString(y) + ")";
}

Vector2I Vector2I::operator+(const Vector2I &other) const {
  return Vector2I(x + other.x, y + other.y);
}

Vector2I Vector2I::operator-(const Vector2I &other) const {
  return Vector2I(x - other.x, y - other.y);
}

Vector2I Vector2I::operator*(const Vector2I &other) const {
  return Vector2I(x * other.x, y * other.y);
}

Vector2I Vector2I::operator*(const float &other) const {
  return Vector2I(x * other, y * other);
}

void Vector2I::operator=(const Vector2I &other) {
  x = other.x;
  y = other.y;
}

void Vector2I::operator+=(const Vector2I &other) {
  x += other.x;
  y += other.y;
}

void Vector2I::operator-=(const Vector2I &other) {
  x -= other.x;
  y -= other.y;
}

bool Vector2I::operator==(const Vector2I &other) const {
  return (x == other.x && y == other.y);
}