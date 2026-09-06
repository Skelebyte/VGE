#include "../inc/matrix.hpp"

using namespace vge;

Matrix::Matrix(const Vector2I &dimensions, bool identity)
    : data(Pointer<float>("Matrix" + ToString(dimensions.x) + "x" +
                          ToString(dimensions.y))) {
  if (dimensions.x == 0 || dimensions.y == 0) {
    Logger::LOG("Dimensions cant be (0,0)!");

    return;
  }

  this->dimensions = dimensions.Abs();

  entries = this->dimensions.x * this->dimensions.y;

  data.Malloc(entries);

  if (identity) {
    Identity();
  } else {
    Zero();
  }
}

Matrix::~Matrix() {}

void Matrix::Identity() {
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

bool Matrix::IsSquareMatrix() const { return dimensions.x == dimensions.y; }

Vector2I Matrix::GetDimensions() const { return dimensions; }

uint32 Matrix::TotalEntries() const { return entries; }

uint32 Matrix::GetColumns() const { return dimensions.x; }

uint32 Matrix::GetRows() const { return dimensions.y; }

void Matrix::Zero() {
  for (int i = 0; i < entries; i++) {
    data[i] = 0;
  }
}

String Matrix::AsString() const {
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

float Matrix::GetEntry(uint32 columnIdx, uint32 rowIdx) const {
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

void Matrix::SetEntry(uint32 columnIdx, uint32 rowIdx, float value) const {
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

Matrix Matrix::operator*(float other) {
  Matrix out(dimensions);

  for (int32 i = 0; i < entries; i++) {
    out.data[i] = data[i] * other;
  }

  return out;
}

// https://stackoverflow.com/a/22149009 -  M Oehm Mar 3, 2014. (CC BY-SA 3.0)
Matrix Matrix::operator*(const Matrix &other) {
  if (GetColumns() != other.GetRows()) {
    Logger::LOG(
        "Cant multiply matrices where the amount of columns of the left matrix "
        "does not match the amount of rows of the right matrix! Returning "
        "a new " +
        ToString(GetColumns()) + "x" + ToString(GetRows()) + " matrix.");
    return Matrix(dimensions);
  }

  // resulting matrix has the amount of columns of the right matrix and the
  // amount of rows the left matrix
  Matrix out = Matrix(Vector2I(other.GetColumns(), GetRows()));

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

void Matrix::operator=(const Matrix &other) {
  for (int i = 0; i < 16; i++) {
    this->data[i] = other.data[i];
  }
}

// 4x4 Matrix Specific Functions

void Matrix::Transform(const Vector3 &position, const Vector3 &rotation,
                       const Vector3 &scale) {
  if (dimensions != Vector2I(4)) {
    Logger::LOG("Cant transform a matrix that is not 4x4!");
    return;
  }

  Matrix posMat(4, true);
  Matrix rotMat(4, true);
  Matrix scaMat(4, true);

  posMat.SetTranslation(position);
  rotMat.SetRotation(rotation);
  scaMat.SetScale(scale);

  *this = (posMat * rotMat * scaMat);
}

void Matrix::SetTranslation(const Vector3 &position) {
  if (dimensions != 4) {
    Logger::LOG("This function only works for 4x4 transformation matrices!");
    return;
  }
  Identity();
  SetEntry(3, 0, position.x);
  SetEntry(3, 1, position.y);
  SetEntry(3, 2, position.z);
}

void Matrix::SetRotation(const Vector3 &rotation) {
  if (dimensions != 4 && dimensions != 3) {
    Logger::LOG("This function only works for 3x3 or 4x4 matrices!");
    return;
  }

  int32 d = dimensions.x;

  Matrix xRot(d, true);
  xRot.SetEntry(1, 1, Mathf::Cos(rotation.x));
  xRot.SetEntry(2, 1, -Mathf::Sin(rotation.x));

  xRot.SetEntry(1, 2, Mathf::Sin(rotation.x));
  xRot.SetEntry(2, 2, Mathf::Cos(rotation.x));

  Matrix yRot(d, true);
  yRot.SetEntry(0, 0, Mathf::Cos(rotation.y));
  yRot.SetEntry(2, 0, Mathf::Sin(rotation.y));

  yRot.SetEntry(0, 2, -Mathf::Sin(rotation.y));
  yRot.SetEntry(2, 2, Mathf::Cos(rotation.y));

  Matrix zRot(d, true);
  zRot.SetEntry(0, 0, Mathf::Cos(rotation.z));
  zRot.SetEntry(1, 0, -Mathf::Sin(rotation.z));
  zRot.SetEntry(0, 1, Mathf::Sin(rotation.z));
  zRot.SetEntry(1, 1, Mathf::Cos(rotation.z));

  *this = (xRot * yRot * zRot);
}

void Matrix::SetScale(const Vector3 &scale) {
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
void Matrix::LookAt(const Vector3 &eye, const Vector3 &eyeUp,
                    const Vector3 &target) {
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
void Matrix::Perspective(float fovDeg, float aspect, float near, float far) {
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
