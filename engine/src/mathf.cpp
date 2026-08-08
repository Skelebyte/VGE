#include "../inc/mathf.hpp"

using namespace vge;

float Mathf::toRadians(float degrees) {
  float result = degrees * M_PI / 180;

  if (result != result) {
    // std::cout << "Mathf::radians: value is NaN, returning 0" << std::endl;
    return 0;
  }

  return result;
}

float Mathf::toDegrees(float radians) {
  float result = radians / M_PI * 180;

  if (result != result) {
    // std::cout << "Mathf::radians: value is NaN, returning 0" << std::endl;
    return 0;
  }

  return result;
}

float Mathf::lerp(float a, float b, float t) { return a + t * (b - a); }

bool Mathf::isZeroApprox(float value) { return std::abs(value) < 0.00001f; }