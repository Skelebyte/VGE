#include "../inc/mathf.hpp"

using namespace vge;

float Mathf::ToRadians(float degrees) {
  float result = degrees * M_PI / 180;

  if (result != result) {
    // std::cout << "Mathf::radians: value is NaN, returning 0" << std::endl;
    return 0;
  }

  return result;
}

float Mathf::ToDegress(float radians) {
  float result = radians / M_PI * 180;

  if (result != result) {
    // std::cout << "Mathf::radians: value is NaN, returning 0" << std::endl;
    return 0;
  }

  return result;
}

float Mathf::Lerp(float a, float b, float t) { return a + t * (b - a); }

bool Mathf::IsZeroApprox(float value) { return std::abs(value) < 0.00001f; }

float Mathf::Min(float a, float b) {
  if (a <= b) {
    return a;
  } else {
    return b;
  }
}

float Mathf::Max(float a, float b) {
  if (a >= b) {
    return a;
  } else {
    return b;
  }
}