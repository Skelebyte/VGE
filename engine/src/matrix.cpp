#include "../inc/matrix.hpp"

using namespace vge;

// Matrix::Matrix(uint32 dimensions, bool identity) {
//   Matrix(Vector2I(dimensions), identity);
// }

Matrix::Matrix(const Vector2I &dimensions, bool identity)
    : data(Pointer<float>("Matrix" + ToString(dimensions.x) + "x" +
                          ToString(dimensions.y))) {
  if (dimensions.x == 0 || dimensions.y == 0) {
    Logger::LOG("Dimensions cant be (0,0)!");

    return;
  }

  this->dimensions = dimensions.Abs();

  values = this->dimensions.x * this->dimensions.y;

  data.Malloc(values);

  if (identity) {
    Identity();
  } else {
    Zero();
  }
}

Matrix::~Matrix() {}

void Matrix::Identity() {
  if (!IsUniformSize()) {
    Logger::LOG("Matrix is not uniform! Cant make identity matrix.");
    return;
  }

  int n = 0;
  for (int i = 0; i < values; i++) {
    if (n == 0) {
      data[i] = 1;
      n = dimensions.x;
    } else {
      data[i] = 0;
      n--;
    }
  }
}

bool Matrix::IsUniformSize() const { return dimensions.x == dimensions.y; }

Vector2I Matrix::GetDimensions() const { return dimensions; }

uint32 Matrix::GetNumberOfValues() const { return values; }

uint32 Matrix::GetColumns() const { return dimensions.x; }

uint32 Matrix::GetRows() const { return dimensions.y; }

void Matrix::Zero() {
  for (int i = 0; i < values; i++) {
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

  data[rowIdx * GetRows() + columnIdx] = value;
}

Matrix Matrix::operator*(float other) {
  Matrix out(dimensions);

  for (int32 i = 0; i < values; i++) {
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
      out.data[row * GetRows() + col] = 0;
      float sum = 0.0f;
      for (int i = 0; i < GetColumns(); i++) {
        sum += data[i * GetRows() + col] * other.data[row * GetColumns() + i];
      }
      // out.data[row * GetRows() + col] = sum;
      out.SetEntry(col, row, sum);
    }
  }

  return out;
}

// void Matrix::operator=(const Matrix &other) {
//   for (int i = 0; i < 16; i++) {
//     this->data[i] = other.data[i];
//   }
// }
