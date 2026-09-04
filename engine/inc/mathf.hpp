#ifndef VGE_MATHF_HPP
#define VGE_MATHF_HPP

#include "common.hpp"
#include <cmath>

namespace vge {

struct Mathf {
  static float ToRadians(float degrees);
  static float ToDegrees(float radians);
  static float Lerp(float a, float b, float t);
  static bool IsZeroApprox(float value);
  static float Min(float a, float b);
  static float Max(float a, float b);
  static float Abs(float a);
};

} // namespace vge

#endif
