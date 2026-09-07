#ifndef VGE_MATRIX_HPP
#define VGE_MATRIX_HPP

#include "common.hpp"
#include "logger.hpp"
#include "mathf.hpp"
#include "memory.hpp"
#include "vector2i.hpp"
#include "vector3.hpp"

namespace vge {
struct Matrix {
  Matrix(const Vector2I &dimensions, bool identity = false);
  ~Matrix();

  void Identity();
  bool IsSquareMatrix() const;
  Vector2I GetDimensions() const;
  uint32 TotalEntries() const;
  uint32 GetColumns() const;
  uint32 GetRows() const;
  void Zero();
  String AsString() const;
  float GetEntry(uint32 column, uint32 row) const;
  void SetEntry(uint32 column, uint32 row, float value) const;

  Matrix operator*(float other);
  Matrix operator*(const Matrix &other);
  void operator=(const Matrix &other);

  // 4x4 Matrix Specific Functions
  void Transform(const Vector3 &position, const Vector3 &rotation,
                 const Vector3 &scale);
  void SetTranslation(const Vector3 &position);
  void
  SetRotation(const Vector3 &rotation); // This function works with 3x3 matrices
  void SetScale(const Vector3 &scale);  // This function works with 3x3 matrices
  // void LookAt(const Vector3 &target, const Vector3 &position,
  //             const Vector3 &forward, const Vector3 &up);
  void LookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &eyeUp);
  void Perspective(float fovDeg, float aspect, float near, float far);

  Pointer<float> data;

protected:
  Vector2I dimensions;
  uint32 entries;
};
} // namespace vge

#endif
