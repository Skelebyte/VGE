#ifndef VGE_MATRIX_HPP
#define VGE_MATRIX_HPP

#include "common.hpp"
#include "logger.hpp"
#include "memory.hpp"
#include "vector2i.hpp"

namespace vge {
struct Matrix {

  Matrix(const Vector2I &dimensions, bool identity = false);
  ~Matrix();

  void Identity();
  bool IsUniformSize() const;
  Vector2I GetDimensions() const;
  uint32 GetNumberOfValues() const;

  Pointer<float> data;

protected:
  Vector2I dim;
  uint32 values;
};
} // namespace vge

#endif