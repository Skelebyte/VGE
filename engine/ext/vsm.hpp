#ifndef VSM_HPP
#define VSM_HPP

#include <cassert>
#include <cmath>
#include <string>

#define VSM_VERSION_STR "1.0.1"

namespace vsm {

struct Mathf {
  static float ToRadians(float _degrees) {
    float result = _degrees * M_PI / 180;

    assert(result == result); // NaN check

    return result;
  }

  static float ToDegrees(float _radians) {
    float result = _radians / M_PI * 180;

    assert(result == result); // NaN check

    return result;
  }

  static float Lerp(float _a, float _b, float _t) {
    return _a + _t * (_b - _a);
  }

  static bool IsZeroApprox(float _a) { return Mathf::Abs(_a) < 0.00001f; }

  static float Min(float _a, float _b) {
    if (_a <= _b) {
      return _a;
    } else {
      return _b;
    }
  }

  static float Max(float _a, float _b) {
    if (_a >= _b) {
      return _a;
    } else {
      return _b;
    }
  }

  static float Abs(float _a) {

    if (_a < 0) {
      return _a - (_a * 2);
    } else {
      return _a;
    }
  }
  static float Sin(float _a) { return std::sin(_a); }

  static float Cos(float _a) { return std::cos(_a); }

  static float Tan(float _a) { return std::tan(_a); }

  static float Sqrt(float _a) { return std::sqrt(_a); }
};

template <uint S, typename T = float> struct Vector {

  virtual T *GetData() { return data; }

protected:
  T data[S];
};

struct Vector3f : Vector<3, float> {
  float x, y, z;

  Vector3f() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }

  Vector3f(float _xyz) {
    x = _xyz;
    y = _xyz;
    z = _xyz;
  }

  Vector3f(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
  }

  float *GetData() override {
    data[0] = x;
    data[1] = y;
    data[2] = z;

    return data;
  }

public:
  static Vector3f Cross(const Vector3f &_a, const Vector3f &_b) {
    return Vector3f(_a.y * _b.z - _a.z * _b.y, _a.z * _b.x - _a.x * _b.z,
                    _a.x * _b.y - _a.y * _b.x);
  }
  static float Dot(const Vector3f &_a, const Vector3f &_b) {
    return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z;
  }

  static Vector3f Lerp(const Vector3f &_a, const Vector3f &_b, float _t) {
    float newX = _a.x + _t * (_b.x - _a.x);
    float newY = _a.y + _t * (_b.y - _a.y);
    float newZ = _a.z + _t * (_b.z - _a.z);

    return Vector3f(newX, newY, newZ);
  }

  float Length() const { return Mathf::Sqrt(x * x + y * y + z * z); }

  // TODO add some sort of check to ensure correct result
  Vector3f Normalized() const {
    Vector3f norm = *this;
    float len = this->Length();

    norm.x /= len;
    norm.y /= len;
    norm.z /= len;

    return norm;
  }

  std::string ToString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " +
           std::to_string(z) + ")";
  }

  Vector3f operator+(const Vector3f &_other) const {
    return Vector3f(x + _other.x, y + _other.y, z + _other.z);
  }

  Vector3f operator-(const Vector3f &_other) const {
    return Vector3f(x - _other.x, y - _other.y, z - _other.z);
  }

  Vector3f operator*(const Vector3f &_other) const {
    return Vector3f(x * _other.x, y * _other.y, z * _other.z);
  }

  Vector3f operator*(const float &_other) const {
    return Vector3f(x * _other, y * _other, z * _other);
  }

  void operator=(const Vector3f &_other) {
    x = _other.x;
    y = _other.y;
    z = _other.z;
  }

  void operator+=(const Vector3f &_other) {
    x += _other.x;
    y += _other.y;
    z += _other.z;
  }

  void operator-=(const Vector3f &_other) {
    x -= _other.x;
    y -= _other.y;
    z -= _other.z;
  }

  bool operator==(const Vector3f &_other) const {
    return (x == _other.x && y == _other.y && z == _other.z);
  }
};

struct Vector3i : Vector<3, int> {
  int x, y, z;

  Vector3i() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }

  Vector3i(int _xyz) {
    x = _xyz;
    y = _xyz;
    z = _xyz;
  }

  Vector3i(int _x, int _y, int _z) {
    x = _x;
    y = _y;
    z = _z;
  }

  int *GetData() override {
    data[0] = x;
    data[1] = y;
    data[2] = z;

    return data;
  }

public:
  static Vector3i Cross(const Vector3i &_a, const Vector3i &_b) {
    return Vector3i(_a.y * _b.z - _a.z * _b.y, _a.z * _b.x - _a.x * _b.z,
                    _a.x * _b.y - _a.y * _b.x);
  }
  static float Dot(const Vector3i &_a, const Vector3i &_b) {
    return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z;
  }

  int Length() const { return Mathf::Sqrt(x * x + y * y + z * z); }

  // TODO add some sort of check to ensure correct result
  Vector3i Normalized() const {
    Vector3i norm = *this;
    int len = this->Length();

    norm.x /= len;
    norm.y /= len;
    norm.z /= len;

    return norm;
  }

  std::string ToString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " +
           std::to_string(z) + ")";
  }

  Vector3i operator+(const Vector3i &_other) const {
    return Vector3i(x + _other.x, y + _other.y, z + _other.z);
  }

  Vector3i operator-(const Vector3i &_other) const {
    return Vector3i(x - _other.x, y - _other.y, z - _other.z);
  }

  Vector3i operator*(const Vector3i &_other) const {
    return Vector3i(x * _other.x, y * _other.y, z * _other.z);
  }

  Vector3i operator*(const int &_other) const {
    return Vector3i(x * _other, y * _other, z * _other);
  }

  void operator=(const Vector3i &_other) {
    x = _other.x;
    y = _other.y;
    z = _other.z;
  }

  void operator+=(const Vector3i &_other) {
    x += _other.x;
    y += _other.y;
    z += _other.z;
  }

  void operator-=(const Vector3i &_other) {
    x -= _other.x;
    y -= _other.y;
    z -= _other.z;
  }

  bool operator==(const Vector3i &_other) const {
    return (x == _other.x && y == _other.y && z == _other.z);
  }
};

struct Vector2f : Vector<2, float> {
  float x, y;

  Vector2f() {
    x = 0.0f;
    y = 0.0f;
  }

  Vector2f(float _xy) {
    x = _xy;
    y = _xy;
  }

  Vector2f(float _x, float _y) {
    x = _x;
    y = _y;
  }

  float *GetData() override {
    data[0] = x;
    data[1] = y;

    return data;
  }

public:
  static float Dot(const Vector2f &_a, const Vector2f &_b) {
    return _a.x * _b.x + _a.y * _b.y;
  }

  static Vector2f Lerp(const Vector2f &_a, const Vector2f &_b, float _t) {
    float newX = _a.x + _t * (_b.x - _a.x);
    float newY = _a.y + _t * (_b.y - _a.y);

    return Vector2f(newX, newY);
  }

  float Length() const { return Mathf::Sqrt(x * x + y * y); }

  // TODO add some sort of check to ensure correct result
  Vector2f Normalized() const {
    Vector2f norm = *this;
    float len = this->Length();

    norm.x /= len;
    norm.y /= len;

    return norm;
  }

  std::string ToString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
  }

  Vector2f operator+(const Vector2f &_other) const {
    return Vector2f(x + _other.x, y + _other.y);
  }

  Vector2f operator-(const Vector2f &_other) const {
    return Vector2f(x - _other.x, y - _other.y);
  }

  Vector2f operator*(const Vector2f &_other) const {
    return Vector2f(x * _other.x, y * _other.y);
  }

  Vector2f operator*(const float &_other) const {
    return Vector2f(x * _other, y * _other);
  }

  void operator=(const Vector2f &_other) {
    x = _other.x;
    y = _other.y;
  }

  void operator+=(const Vector2f &_other) {
    x += _other.x;
    y += _other.y;
  }

  void operator-=(const Vector2f &_other) {
    x -= _other.x;
    y -= _other.y;
  }

  bool operator==(const Vector2f &_other) const {
    return (x == _other.x && y == _other.y);
  }
};

struct Vector2i : Vector<2, int> {
  int x, y;

  Vector2i() {
    x = 0.0f;
    y = 0.0f;
  }

  Vector2i(int _xy) {
    x = _xy;
    y = _xy;
  }

  Vector2i(int _x, int _y) {
    x = _x;
    y = _y;
  }

  int *GetData() override {
    data[0] = x;
    data[1] = y;

    return data;
  }

public:
  static float Dot(const Vector2f &_a, const Vector2f &_b) {
    return _a.x * _b.x + _a.y * _b.y;
  }

  float Length() const { return Mathf::Sqrt(x * x + y * y); }

  // TODO add some sort of check to ensure correct result
  // TODO figure out if you can normalize an integer vector
  // Vector2f Normalized() const {
  //   Vector2f norm = *this;
  //   float len = this->Length();

  //   norm.x /= len;
  //   norm.y /= len;

  //   return norm;
  // }

  std::string ToString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
  }

  Vector2i operator+(const Vector2i &_other) const {
    return Vector2i(x + _other.x, y + _other.y);
  }

  Vector2i operator-(const Vector2i &_other) const {
    return Vector2i(x - _other.x, y - _other.y);
  }

  Vector2i operator*(const Vector2i &_other) const {
    return Vector2i(x * _other.x, y * _other.y);
  }

  Vector2i operator*(const float &_other) const {
    return Vector2i(x * _other, y * _other);
  }

  void operator=(const Vector2i &_other) {
    x = _other.x;
    y = _other.y;
  }

  void operator+=(const Vector2i &_other) {
    x += _other.x;
    y += _other.y;
  }

  void operator-=(const Vector2i &_other) {
    x -= _other.x;
    y -= _other.y;
  }

  bool operator==(const Vector2i &_other) const {
    return (x == _other.x && y == _other.y);
  }
};

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
      // Logger::LOG("Matrix is not square! Cant make identity matrix.");
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
      // Logger::LOG("There are only " + ToString(COLUMNS) + " (highest index: "
      // +
      //             ToString(COLUMNS - 1) + ") columns in this matrix! Column "
      //             + ToString(cIdx) + " is out of bounds!");
      return 0.0f;
    }

    if (rIdx > ROWS) {
      // Logger::LOG("There are only " + ToString(ROWS) + " (highest index: " +
      //             ToString(ROWS - 1) + ") rows in this matrix! Row " +
      //             ToString(rIdx) + " is out of bounds!");
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
      // Logger::LOG("There are only " + ToString(COLUMNS) + " (highest index: "
      // +
      //             ToString(COLUMNS - 1) + ") columns in this matrix! Column "
      //             + ToString(cIdx) + " is out of bounds!");
      return;
    }

    if (rIdx > ROWS) {
      // Logger::LOG("There are only " + ToString(ROWS) + " (highest index: " +
      //             ToString(ROWS - 1) + ") rows in this matrix! Row " +
      //             ToString(rIdx) + " is out of bounds!");
      return;
    }

    data[rIdx + major * cIdx] = value;
  }

  std::string ToString() const {
    std::string out = "";

    for (int row = 0; row < ROWS; row++) {
      out += "[ ";
      for (int col = 0; col < COLUMNS; col++) {
        out += std::to_string(GetEntry(col, row)) + " ";
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

    // AMOUNT OF COLUMNS OF THE LEFT MATRIX MUST BE EQUAL TO THE AMOUNT OF ROWS
    // OF THE LEFT MATRIX
    assert(COLUMNS == other.ROWS);

    // resulting matrix has the amount of columns of the right matrix and
    // the amount of rows the left matrix
    Matrix<ROWS, C2> out;

    for (int row = 0; row < ROWS; row++) {
      for (int col = 0; col < other.COLUMNS; col++) {
        out.data[row * ROWS + col] = 0;
        float sum = 0.0f;
        for (int i = 0; i < COLUMNS; i++) {
          sum += data[i * ROWS + col] * other.data[row * other.ROWS + i];
        }
        out.data[row * ROWS + col] = sum;
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

  void Transform(const Vector3f &position, const Vector3f &rotation,
                 const Vector3f &scale) {

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

  void SetTranslation(const Vector3f &position) {
    // This function only works with 4x4 matrices!
    assert(R == 4 && C == 4);

    Identity();

    SetEntry(3, 0, position.x);
    SetEntry(3, 1, position.y);
    SetEntry(3, 2, position.z);
  }

  // https://github.com/g-truc/glm/blob/6f14f4792a0cde5d0cf2c910506724d61cb95834/glm/ext/matrix_transform.inl#L153
  void LookAt(const Vector3f &eye, const Vector3f &target,
              const Vector3f &eyeUp) {
    // This function only works with 4x4 matrices!
    assert(R == 4 && C == 4);

    Vector3f fwd = (target - eye).Normalized(); // forward
    Vector3f rht = Vector3f::Cross(fwd, eyeUp); // right
    Vector3f up = Vector3f::Cross(rht, fwd);    // up

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

    SetEntry(3, 0, -Vector3f::Dot(rht, eye));
    SetEntry(3, 1, -Vector3f::Dot(up, eye));
    SetEntry(3, 2, Vector3f::Dot(fwd, eye));
  }

  // https://stackoverflow.com/a/53366142 - Pmsmm Nov 18, 2018 (CC BY-SA 4.0)
  void Perspective(float fovDeg, float aspect, float near, float far) {
    // This function only works with 4x4 matrices!
    static_assert(R == 4 && C == 4, "shitty");

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

  void SetRotation(const Vector3f &rotation) {
    // This function only works with 3x3 or larger matrices!
    assert(R >= 3 && C >= 3);

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
  void SetScale(const Vector3f &scale) {
    // This function only works with 3x3 or larger matrices!
    assert(R >= 3 && C >= 3);

    Identity();
    SetEntry(0, 0, scale.x);
    SetEntry(1, 1, scale.y);
    SetEntry(2, 2, scale.z);
  }
};

} // namespace vsm

#endif
