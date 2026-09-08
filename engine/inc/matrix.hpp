#ifndef VGE_MATRIX_HPP
#define VGE_MATRIX_HPP

#include "common.hpp"
#include "logger.hpp"
#include "mathf.hpp"
#include "memory.hpp"
#include "vector2i.hpp"
#include "vector3.hpp"

namespace vge {

template <uint columns = 1, uint rows = 1> struct Matrix {
  Matrix(bool identity = false, uint c = columns, uint r = rows) {
    if (c == 0 || r == 0) {
      Logger::LOG("Dimensions cant be (0, 0)!");

      return;
    }

    this->dimensions.x = c;
    this->dimensions.y = r;

    entries = this->dimensions.x * this->dimensions.y;

    if (identity) {
      Identity();
    } else {
      Zero();
    }
  }

  void Identity() {
    if (!IsSquareMatrix()) {
      Logger::LOG("Matrix is not uniform! Cant make identity matrix.");
      return;
    }

    int n = 0;
    for (int i = 0; i < entries; i++) {
      if (n == 0) {
        data[i] = 1;
        n = dimensions.x;
      } else {
        data[i] = 0;
        n--;
      }
    }
  }

  bool IsSquareMatrix() const { return dimensions.x == dimensions.y; }

  uint TotalEntries() const { return entries; }

  uint GetColumns() const { return dimensions.x; }

  uint GetRows() const { return dimensions.y; }

  void Zero() {
    for (int i = 0; i < entries; i++) {
      data[i] = 0;
    }
  }
  String AsString() const {
    String out = "";

    for (int row = 0; row < GetRows(); row++) {
      out += "[ ";
      for (int col = 0; col < GetColumns(); col++) {
        out += ToString(data[col * GetRows() + row]) + " ";
      }
      out += "]\n";
    }

    return out;
  }

  float GetEntry(uint columnIdx, uint rowIdx) const {
    if (columnIdx > GetColumns() - 1) {
      Logger::LOG("There are only " + ToString(GetColumns()) + " (" +
                  ToString(GetColumns() - 1) +
                  ") columns in this matrix! Column " + ToString(columnIdx) +
                  " is out of bounds!");
      return 0.0f;
    }

    if (rowIdx > GetRows() - 1) {
      Logger::LOG("There are only " + ToString(GetRows()) + " (" +
                  ToString(GetRows() - 1) + ") rows in this matrix! Row " +
                  ToString(rowIdx) + " is out of bounds!");
      return 0.0f;
    }

    return data[columnIdx * GetRows() + rowIdx];
  }
  void SetEntry(uint columnIdx, uint rowIdx, float value) {
    if (columnIdx > GetColumns() - 1) {
      Logger::LOG("There are only " + ToString(GetColumns()) + " (" +
                  ToString(GetColumns() - 1) +
                  ") columns in this matrix! Column " + ToString(columnIdx) +
                  " is out of bounds!");
      return;
    }

    if (rowIdx > GetRows() - 1) {
      Logger::LOG("There are only " + ToString(GetRows()) + " (" +
                  ToString(GetRows() - 1) + ") rows in this matrix! Row " +
                  ToString(rowIdx) + " is out of bounds!");
      return;
    }

    // i think i flipped rowIdx and columnIdx by accident
    // data[rowIdx * GetRows() + columnIdx] = value;
    data[columnIdx * GetRows() + rowIdx] = value;
  }

  Matrix operator*(float other) {
    Matrix<> out(false, dimensions.x, dimensions.y);

    for (int i = 0; i < entries; i++) {
      out.data[i] = data[i] * other;
    }

    return out;
  }

  // https://stackoverflow.com/a/22149009 -  M Oehm Mar 3, 2014. (CC BY-SA 3.0)
  Matrix operator*(const Matrix &other) {
    if (GetColumns() != other.GetRows()) {
      Logger::LOG(
          "Cant multiply matrices where the amount of columns of the left "
          "matrix "
          "does not match the amount of rows of the right matrix! Returning "
          "a new " +
          ToString(GetColumns()) + "x" + ToString(GetRows()) + " matrix.");
      return Matrix(false, GetColumns(), GetRows());
    }

    // resulting matrix has the amount of columns of the right matrix and the
    // amount of rows the left matrix
    Matrix out(false, other.GetColumns(), GetRows());

    for (int row = 0; row < GetRows(); row++) {
      for (int col = 0; col < other.GetColumns(); col++) {
        // out.data[row * GetRows() + col] = 0;
        out.SetEntry(col, row, 0.0f);
        float sum = 0.0f;
        for (int i = 0; i < GetColumns(); i++) {
          sum += data[i * GetRows() + col] *
                 other.data[row * other.GetColumns() +
                            i]; // this was this->GetColumns()
        }
        // out.data[row * GetRows() + col] = sum;
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

  // 4x4 Matrix Specific Functions
  void Transform(const Vector3 &position, const Vector3 &rotation,
                 const Vector3 &scale) {
    if (dimensions != Vector2I(4)) {
      Logger::LOG("Cant transform a matrix that is not 4x4!");
      return;
    }

    Matrix<4, 4> posMat(true);
    Matrix<4, 4> rotMat(true);
    Matrix<4, 4> scaMat(true);

    posMat.SetTranslation(position);
    rotMat.SetRotation(rotation);
    scaMat.SetScale(scale);

    *this = (posMat * rotMat * scaMat);
  }
  void SetTranslation(const Vector3 &position) {
    if (dimensions != 4) {
      Logger::LOG("This function only works for 4x4 transformation matrices!");
      return;
    }
    Identity();
    SetEntry(3, 0, position.x);
    SetEntry(3, 1, position.y);
    SetEntry(3, 2, position.z);
  }
  // This function works with 3x3 and 4x4 matrices

  void SetRotation(const Vector3 &rotation) {
#if (dimensions == 4)
    Matrix<4, 4> xRot(true);
    xRot.SetEntry(1, 1, Mathf::Cos(rotation.x));
    xRot.SetEntry(2, 1, -Mathf::Sin(rotation.x));

    xRot.SetEntry(1, 2, Mathf::Sin(rotation.x));
    xRot.SetEntry(2, 2, Mathf::Cos(rotation.x));

    Matrix<4, 4> yRot(true);
    yRot.SetEntry(0, 0, Mathf::Cos(rotation.y));
    yRot.SetEntry(2, 0, Mathf::Sin(rotation.y));

    yRot.SetEntry(0, 2, -Mathf::Sin(rotation.y));
    yRot.SetEntry(2, 2, Mathf::Cos(rotation.y));

    Matrix<4, 4> zRot(true);
    zRot.SetEntry(0, 0, Mathf::Cos(rotation.z));
    zRot.SetEntry(1, 0, -Mathf::Sin(rotation.z));
    zRot.SetEntry(0, 1, Mathf::Sin(rotation.z));
    zRot.SetEntry(1, 1, Mathf::Cos(rotation.z));

    *this = (xRot * yRot * zRot);
    return;
#endif
#if (dimensions == 3)

    Matrix<3, 3> xRot(true);
    xRot.SetEntry(1, 1, Mathf::Cos(rotation.x));
    xRot.SetEntry(2, 1, -Mathf::Sin(rotation.x));

    xRot.SetEntry(1, 2, Mathf::Sin(rotation.x));
    xRot.SetEntry(2, 2, Mathf::Cos(rotation.x));

    Matrix<3, 3> yRot(true);
    yRot.SetEntry(0, 0, Mathf::Cos(rotation.y));
    yRot.SetEntry(2, 0, Mathf::Sin(rotation.y));

    yRot.SetEntry(0, 2, -Mathf::Sin(rotation.y));
    yRot.SetEntry(2, 2, Mathf::Cos(rotation.y));

    Matrix<3, 3> zRot(true);
    zRot.SetEntry(0, 0, Mathf::Cos(rotation.z));
    zRot.SetEntry(1, 0, -Mathf::Sin(rotation.z));
    zRot.SetEntry(0, 1, Mathf::Sin(rotation.z));
    zRot.SetEntry(1, 1, Mathf::Cos(rotation.z));

    *this = (xRot * yRot * zRot);
#endif

    Logger::LOG("This function only works for 3x3 or 4x4 matrices!");
  }

  // This function works with 3x3 and 4x4 matrices
  void SetScale(const Vector3 &scale) {
    if (dimensions != 4 && dimensions != 3) {
      Logger::LOG("This function only works for 3x3 or 4x4 matrices!");
      return;
    }

    Identity();
    SetEntry(0, 0, scale.x);
    SetEntry(1, 1, scale.y);
    SetEntry(2, 2, scale.z);
  }
  // https://github.com/g-truc/glm/blob/6f14f4792a0cde5d0cf2c910506724d61cb95834/glm/ext/matrix_transform.inl#L153
  void LookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &eyeUp) {
    if (dimensions != 4) {
      Logger::LOG("This function only works with 4x4 matrices!");
      return;
    }

    Vector3 fwd = (target - eye).Normalized(); // forward
    Vector3 rht = Vector3::Cross(fwd, eyeUp);  // right
    Vector3 up = Vector3::Cross(rht, fwd);     // up

    Identity();
    SetEntry(0, 0, rht.x);
    SetEntry(0, 1, rht.y);
    SetEntry(0, 2, rht.z);

    SetEntry(1, 0, up.x);
    SetEntry(1, 1, up.y);
    SetEntry(1, 2, up.z);

    SetEntry(2, 0, -fwd.x);
    SetEntry(2, 1, -fwd.y);
    SetEntry(2, 2, -fwd.z);

    SetEntry(3, 0, -Vector3::Dot(rht, eye));
    SetEntry(3, 1, -Vector3::Dot(up, eye));
    SetEntry(3, 2, Vector3::Dot(fwd, eye));
  }

  // https://stackoverflow.com/a/53366142 - Pmsmm Nov 18, 2018 (CC BY-SA 4.0)
  void Perspective(float fovDeg, float aspect, float near, float far) {
    if (dimensions != 4) {
      Logger::LOG("This function only works with 4x4 matrices!");
      return;
    }

    float fovRad = Mathf::ToRadians(fovDeg);
    float tanFov = Mathf::Tan(fovRad / 2);

    Zero();
    SetEntry(0, 0, 1 / (aspect * tanFov));
    SetEntry(1, 1, 1 / tanFov);
    SetEntry(2, 2, -((far + near) / (far - near)));
    SetEntry(2, 3, -1);
    SetEntry(3, 2, -((2 * far * near) / (far - near)));
  }

  float data[columns * rows];

protected:
  Vector2I dimensions;
  uint entries;
};
} // namespace vge

#endif
