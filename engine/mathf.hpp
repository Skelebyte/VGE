#ifndef VGE_MATHF_HPP
#define VGE_MATHF_HPP

#include <cmath>

namespace vge {

struct Mathf {
  static float toRadians(float degrees);
  static float toDegrees(float radians);
  static float lerp(float a, float b, float t);
  static bool isZeroApprox(float value);
};

} // namespace vge

#endif