#include "../inc/matrix.hpp"

using namespace vge;

Matrix::Matrix(const Vector2I &dimensions, bool identity) {
  if (dimensions.x == 0 || dimensions.y == 0) {
    Logger::LOG("Dimensions cant be (0,0)!");

    return;
  }

  dim = dimensions.Abs();

  values = dim.x * dim.y;

  // data = Pointer<float>();
  data.Malloc(values);

  if (identity) {
    Identity();
  } else {
    for (int i = 0; i < values; i++) {
      data[i] = 0;
    }
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
      n = dim.x;
    } else {
      data[i] = 0;
      n--;
    }
  }
}

bool Matrix::IsUniformSize() const { return dim.x == dim.y; }

Vector2I Matrix::GetDimensions() const { return dim; }

uint32 Matrix::GetNumberOfValues() const { return values; }