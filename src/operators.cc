#include "s21_matrix_oop.h"

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  Cpy(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix tmp(*this);
  tmp.SumMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix tmp(*this);
  tmp.SubMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}

S21Matrix operator*(double value, const S21Matrix& other) {
  S21Matrix tmp(other);
  tmp.MulNumber(value);
  return tmp;
}

S21Matrix operator*(const S21Matrix& other, double value) {
  S21Matrix tmp(other);
  tmp.MulNumber(value);
  return tmp;
}

void S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
}

void S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
}

void S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
}

void S21Matrix::operator*=(double value) {
  MulNumber(value);
}

double& S21Matrix::operator()(int i, int j) const {
  if (cols_ < 1 || rows_ < 1 || i < 0 || j < 0 || (i > rows_ || j > cols_)) {
    throw std::out_of_range("Incorrect input");
  } else
    return matrix_[i][j];
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept{
  bool res = EqMatrix(other);
  return res;
}