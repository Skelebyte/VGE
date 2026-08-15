#ifndef VGE_MATHF_HPP
#define VGE_MATHF_HPP

#include <cmath>

namespace vge {

struct Mathf {
  static float ToRadians(float degrees);
  static float ToDegress(float radians);
  static float Lerp(float a, float b, float t);
  static bool IsZeroApprox(float value);
};

} // namespace vge

#endif