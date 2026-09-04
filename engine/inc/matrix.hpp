#ifndef VGE_MATRIX_HPP
#define VGE_MATRIX_HPP

#include "common.hpp"
#include "logger.hpp"
#include "memory.hpp"
#include "vector2i.hpp"

namespace vge {
struct Matrix {
  // Matrix(uint32 dimensions, bool identity = false);
  Matrix(const Vector2I &dimensions, bool identity = false);
  ~Matrix();

  void Identity();
  bool IsUniformSize() const;
  Vector2I GetDimensions() const;
  uint32 GetNumberOfValues() const;
  uint32 GetColumns() const;
  uint32 GetRows() const;
  void Zero();
  String AsString() const;
  float GetEntry(uint32 column, uint32 row) const;
  void SetEntry(uint32 column, uint32 row, float value) const;

  Matrix operator*(float other);
  Matrix operator*(const Matrix &other);
  // void operator=(const Matrix &other);

  Pointer<float> data;

protected:
  Vector2I dimensions;
  uint32 values;
};
} // namespace vge

#endif
