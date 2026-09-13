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

  float data[R * C];

  static constexpr uint ROWS = R;
  static constexpr uint COLUMNS = C;
  static constexpr uint ENTRIES = R * C;

  Matrix(bool identity = false) {
    Zero();
    if (identity) {
      Identity();
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

  // ! not entirely happy with calling the 4th arg "major" as i dont think its
  // ! intirely accurate (as in if its columns major use ROWS, if row major use
  // ! COLUMNS).
  float GetEntry(uint cIdx, uint rIdx, uint major = ROWS) const {
    if (cIdx > COLUMNS) {
      Logger::LOG("There are only " + ToString(COLUMNS) + " (highest index: " +
                  ToString(COLUMNS - 1) + ") columns in this matrix! Column " +
                  ToString(cIdx) + " is out of bounds!");
      return 0.0f;
    }

    if (rIdx > ROWS) {
      Logger::LOG("There are only " + ToString(ROWS) + " (highest index: " +
                  ToString(ROWS - 1) + ") rows in this matrix! Row " +
                  ToString(rIdx) + " is out of bounds!");
      return 0.0f;
    }

    return data[rIdx + major * cIdx];
  }

  /* !
   * not entirely happy with calling the 4th arg "major" as i dont think its
   * intirely accurate (as in if its columns major use ROWS, if row major use
   * COLUMNS).
   */
  void SetEntry(uint cIdx, uint rIdx, float value, uint major = ROWS) {
    if (cIdx > COLUMNS) {
      Logger::LOG("There are only " + ToString(COLUMNS) + " (highest index: " +
                  ToString(COLUMNS - 1) + ") columns in this matrix! Column " +
                  ToString(cIdx) + " is out of bounds!");
      return;
    }

    if (rIdx > ROWS) {
      Logger::LOG("There are only " + ToString(ROWS) + " (highest index: " +
                  ToString(ROWS - 1) + ") rows in this matrix! Row " +
                  ToString(rIdx) + " is out of bounds!");
      return;
    }

    data[rIdx + major * cIdx] = value;
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

    Logger::ASSERT(COLUMNS == other.ROWS,
                   "Amount of columns of the left matrix must be equal to the "
                   "amount of rows of the right matrix");

    // resulting matrix has the amount of columns of the right matrix and
    // the amount of rows the left matrix
    Matrix<ROWS, C2> out;

    for (int row = 0; row < ROWS; row++) {
      for (int col = 0; col < other.COLUMNS; col++) {
        out.data[row * ROWS + col] = 0;
        // out.SetEntry(col, row, 0.0f);
        float sum = 0.0f;
        for (int i = 0; i < COLUMNS; i++) {
          // sum += GetEntry(col, row, ROWS) *
          //        other.GetEntry(col, row, other.COLUMNS);
          sum += data[i * ROWS + col] * other.data[row * other.ROWS + i];
        }
        out.data[row * ROWS + col] = sum;
        // out.SetEntry(col, row, sum);
      }
    }

    return out;
  }

  void operator=(const Matrix<R, C> &other) {
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

  /* ------------ 4x4 Matrix Specific Functions ------------ */

  void Transform(const Vector3 &position, const Vector3 &rotation,
                 const Vector3 &scale) {

    static_assert(R == 4 && C == 4,
                  "This function only works with 4x4 matrices!");

    // Logger::ASSERT(R == 4 && C == 4,
    //                "This function only works with 4x4 matrices!");

    Identity();

    Matrix<4, 4> pos(true);
    pos.SetTranslation(position);
    Matrix<4, 4> rot(true);
    rot.SetRotation(rotation);
    Matrix<4, 4> sca(true);
    sca.SetScale(scale);

    *this = (pos * rot * sca);
  }

  void SetTranslation(const Vector3 &position) {
    Logger::ASSERT(R == 4 && C == 4,
                   "This function only works with 4x4 matrices!");

    Identity();

    SetEntry(3, 0, position.x);
    SetEntry(3, 1, position.y);
    SetEntry(3, 2, position.z);
  }

  // https://github.com/g-truc/glm/blob/6f14f4792a0cde5d0cf2c910506724d61cb95834/glm/ext/matrix_transform.inl#L153
  void LookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &eyeUp) {
    Logger::ASSERT(R == 4 && C == 4,
                   "This function only works with 4x4 matrices!");

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
    Logger::ASSERT(R == 4 && C == 4,
                   "This function only works with 4x4 matrices!");

    float fovRad = Mathf::ToRadians(fovDeg);
    float tanFov = Mathf::Tan(fovRad / 2);

    Zero();
    SetEntry(0, 0, 1 / (aspect * tanFov));
    SetEntry(1, 1, 1 / tanFov);
    SetEntry(2, 2, -((far + near) / (far - near)));
    SetEntry(2, 3, -1);
    SetEntry(3, 2, -((2 * far * near) / (far - near)));
  }

  /* ------------ 3x3 and larger Matrix Specific Functions ------------ */

  void SetRotation(const Vector3 &rotation) {
    Logger::ASSERT(R >= 3 && C >= 3,
                   "This function only works with 3x3 or larger matrices!");

    Matrix<ROWS, COLUMNS> xRot(true);
    xRot.SetEntry(1, 1, Mathf::Cos(rotation.x));
    xRot.SetEntry(2, 1, -Mathf::Sin(rotation.x));

    xRot.SetEntry(1, 2, Mathf::Sin(rotation.x));
    xRot.SetEntry(2, 2, Mathf::Cos(rotation.x));

    Matrix<ROWS, COLUMNS> yRot(true);
    yRot.SetEntry(0, 0, Mathf::Cos(rotation.y));
    yRot.SetEntry(2, 0, Mathf::Sin(rotation.y));

    yRot.SetEntry(0, 2, -Mathf::Sin(rotation.y));
    yRot.SetEntry(2, 2, Mathf::Cos(rotation.y));

    Matrix<ROWS, COLUMNS> zRot(true);
    zRot.SetEntry(0, 0, Mathf::Cos(rotation.z));
    zRot.SetEntry(1, 0, -Mathf::Sin(rotation.z));
    zRot.SetEntry(0, 1, Mathf::Sin(rotation.z));
    zRot.SetEntry(1, 1, Mathf::Cos(rotation.z));

    *this = (xRot * yRot * zRot);
  }
  void SetScale(const Vector3 &scale) {
    Logger::ASSERT(R >= 3 && C >= 3,
                   "This function only works with 3x3 or larger matrices!");

    Identity();
    SetEntry(0, 0, scale.x);
    SetEntry(1, 1, scale.y);
    SetEntry(2, 2, scale.z);
  }
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
