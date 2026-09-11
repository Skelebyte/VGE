#ifndef VGE_MATRIX_HPP
#define VGE_MATRIX_HPP

#include "common.hpp"
#include "logger.hpp"
#include "mathf.hpp"
#include "memory.hpp"
#include "vector2i.hpp"
#include "vector3.hpp"

namespace vge {

template <uint R, uint C> struct Matrix {

  Matrix(bool identity = false) {
    if (identity) {
      Identity();
    } else {
      Zero();
    }
  }

  void Zero() {
    for (int i = 0; i < ENTRIES; i++) {
      data[i] = 0;
    }
  }

  void Identity() {
    if (!IsSquareMatrix()) {
      Logger::LOG("Matrix is not square! Cant make identity matrix.");
      return;
    }

    int n = 0;
    for (int i = 0; i < ENTRIES; i++) {
      if (n == 0) {
        data[i] = 1;
        n = COLUMNS;
      } else {
        data[i] = 0;
        n--;
      }
    }
  }

  bool IsSquareMatrix() const { return COLUMNS == ROWS; }

  float GetEntry(uint c, uint r) const {
    if (c > COLUMNS - 1) {
      Logger::LOG("There are only " + ToString(COLUMNS) + " (" +
                  ToString(COLUMNS - 1) + ") columns in this matrix! Column " +
                  ToString(c) + " is out of bounds!");
      return 0.0f;
    }

    if (r > ROWS - 1) {
      Logger::LOG("There are only " + ToString(ROWS) + " (" +
                  ToString(ROWS - 1) + ") rows in this matrix! Row " +
                  ToString(r) + " is out of bounds!");
      return 0.0f;
    }

    return data[r * ROWS + c];
  }

  void SetEntry(uint c, uint r, float value) {
    if (c > COLUMNS - 1) {
      Logger::LOG("There are only " + ToString(COLUMNS) + " (" +
                  ToString(COLUMNS - 1) + ") columns in this matrix! Column " +
                  ToString(c) + " is out of bounds!");
      return;
    }

    if (r > ROWS - 1) {
      Logger::LOG("There are only " + ToString(ROWS) + " (" +
                  ToString(ROWS - 1) + ") rows in this matrix! Row " +
                  ToString(r) + " is out of bounds!");
      return;
    }

    data[r * ROWS + c] = value;
  }

  String AsString() const {
    String out = "";

    for (int row = 0; row < ROWS; row++) {
      out += "[ ";
      for (int col = 0; col < COLUMNS; col++) {
        out += ToString(GetEntry(col, row)) + " ";
      }
      out += "]\n";
    }

    return out;
  }

  Matrix operator*(float other) {
    Matrix<R, C> out;

    for (int i = 0; i < ENTRIES; i++) {
      out.data[i] = data[i] * other;
    }

    return out;
  }

  // https://stackoverflow.com/a/22149009 -  M Oehm Mar 3, 2014. (CC
  // BY-SA 3.0)
  template <uint R2 = R, uint C2 = 1>
  Matrix<R2, C2> operator*(const Matrix<C, C2> &other) {
    std::cout << "R: " << R << std::endl;
    std::cout << "C2: " << C2 << std::endl;

    if (COLUMNS != other.ROWS) {
      Logger::LOG_FATAL(
          "Cant multiply matrices where the amount of columns of the left "
          "matrix "
          "does not match the amount of rows of the right matrix! ");
      return Matrix<ROWS, C2>();
    }

    // resulting matrix has the amount of columns of the right matrix and
    // the amount of rows the left matrix
    Matrix<ROWS, C2> out;

    for (int row = 0; row < ROWS; row++) {
      for (int col = 0; col < other.COLUMNS; col++) {
        // out.data[row * ROWS + col] = 0;
        out.SetEntry(col, row, 0.0f);
        float sum = 0.0f;
        for (int i = 0; i < COLUMNS; i++) {
          sum += data[i * ROWS + col] * other.data[row * other.COLUMNS + i];
        }
        // out.data[row * ROWS + col] = sum;
        out.SetEntry(col, row, sum);
      }
    }

    return out;
  }

  void operator=(const Matrix &other) {
    for (int i = 0; i < 16; i++) {
      this->data[i] = other.data[i];
    }
  }

  float &operator[](uint i) {
    if (i < 0)
      return data[0];
    if (i > ENTRIES)
      return data[0];

    return data[i];
  }

  float &operator[](uint i) const {
    if (i < 0)
      return data[0];
    if (i > ENTRIES)
      return data[0];

    return data[i];
  }

  float data[C * R];

  static constexpr uint COLUMNS = C;
  static constexpr uint ROWS = R;
  static constexpr uint ENTRIES = C * R;
};

// struct Matrix {
//   Matrix(const Vector2I &dimensions, bool identity = false);
//   ~Matrix();

//   void Identity();
//   bool IsSquareMatrix() const;
//   Vector2I GetDimensions() const;
//   uint TotalEntries() const;
//   void Zero();
//   String AsString() const;
//   float GetEntry(uint column, uint row) const;
//   void SetEntry(uint column, uint row, float value) const;

//   Matrix operator*(float other);
//   Matrix operator*(const Matrix &other);
//   void operator=(const Matrix &other);

//   // 4x4 Matrix Specific Functions
//   void Transform(const Vector3 &position, const Vector3 &rotation,
//                  const Vector3 &scale);
//   void SetTranslation(const Vector3 &position);
//   // This function works with 3x3 and 4x4  matrices
//   void SetRotation(const Vector3 &rotation);
//   // This function works with 3x3 and 4x4  matrices
//   void SetScale(const Vector3 &scale);
//   void LookAt(const Vector3 &eye, const Vector3 &target, const Vector3
//   &eyeUp); void Perspective(float fovDeg, float aspect, float near, float
//   far);

//   float data;

// protected:
//   Vector2I dimensions;
//   uint entries;
// };
} // namespace vge

#endif
