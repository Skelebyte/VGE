#ifndef VGE_MATRIX3_HPP
#define VGE_MATRIX3_HPP

#include "common.hpp"
#include "logger.hpp"
#include "matrix.hpp"
#include "memory.hpp"
#include "vector3.hpp"

namespace vge {
struct Matrix3x3 : Matrix {

  Matrix3x3(bool identity = false);
  ~Matrix3x3();
};
} // namespace vge

#endif