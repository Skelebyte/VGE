#include "../inc/mathf.hpp"
#include <cstdlib>

using namespace vge;

float Mathf::ToRadians(float degrees) {
  float result = degrees * M_PI / 180;

  if (result != result) {
    // std::cout << "Mathf::radians: value is NaN, returning 0" << std::endl;
    return 0;
  }

  return result;
}

float Mathf::ToDegrees(float radians) {
  float result = radians / M_PI * 180;

  if (result != result) {
    // std::cout << "Mathf::radians: value is NaN, returning 0" << std::endl;
    return 0;
  }

  return result;
}

float Mathf::Lerp(float a, float b, float t) { return a + t * (b - a); }

bool Mathf::IsZeroApprox(float value) { return Mathf::Abs(value) < 0.00001f; }

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

float Mathf::Abs(float a) {

  if (a < 0) {
    return a - (a * 2);
  } else {
    return a;
  }
}
