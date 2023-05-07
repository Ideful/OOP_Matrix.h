#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool res = true;
  if (cols_ == other.cols_ && rows_ == other.rows_ && cols_ > 0 && rows_ > 0) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-5) res = false;
      }
    }
  } else
    res = false;
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if ((cols_ < 1 || rows_ < 1) || cols_ != other.cols_ ||
      rows_ != other.rows_) {
    throw std::out_of_range("Incorrect input");
  } else if (cols_ == other.cols_ && rows_ == other.rows_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if ((cols_ < 1 || rows_ < 1) || cols_ != other.cols_ ||
      rows_ != other.rows_) {
    throw std::out_of_range("Incorrect input");
  } else if (cols_ == other.cols_ && rows_ == other.rows_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (rows_ > 0 && cols_ > 0) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] *= num;
      }
    }
  } else {
    throw std::out_of_range("Incorrect input");
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (rows_ > 0 && cols_ > 0 && other.cols_ > 0 && other.rows_ > 0 &&
      (cols_ == other.rows_)) {
    S21Matrix tmp(rows_, other.cols_);
    for (int i = 0; i < tmp.rows_; i++) {
      for (int j = 0; j < tmp.cols_; j++) {
        tmp.matrix_[i][j] = 0;
        for (int k = 0; k < cols_; k++) {
          tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    Cpy(tmp);
  } else {
    throw std::out_of_range("Incorrect input");
  }
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix tmp(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp.matrix_[j][i] = matrix_[i][j];
    }
  }
  return tmp;
}

S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix tmp(rows_, cols_);
  if (rows_ == cols_ && rows_ > 0 && cols_ > 0) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix calc = Minor(j, i);
        tmp.matrix_[i][j] = calc.Determinant() * pow(-1, i + j);
      }
    }
  } else {
    throw std::out_of_range("Incorrect input");
  }
  return tmp;
}

double S21Matrix::Determinant() const {
  double res = 0;
  if (cols_ == 1)
    res += matrix_[0][0];
  else if (cols_ == 2)
    res += matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  else if (cols_ >= 3) {
    for (int i = 0; i < cols_; i++) {
      S21Matrix minor = Minor(i, 0);
      if (i % 2 == 0)
        res += minor.Determinant() * matrix_[0][i];
      else if (i % 2 == 1)
        res -= minor.Determinant() * matrix_[0][i];
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() const {
  S21Matrix tmp;
  double det = Determinant();
  if (cols_ == rows_ && det != 0) {
    if (cols_ == 1) {
      tmp.rows_ = 1;
      tmp.cols_ = 1;
      tmp.matrix_ = new double*[1];
      tmp.matrix_[0] = new double[1];
      tmp.matrix_[0][0] = 1 / matrix_[0][0];
    } else {
      tmp = CalcComplements().Transpose();
      tmp.MulNumber(1 / det);
    }
  } else {
    throw std::out_of_range("Incorrect input");
  }
  return tmp;
}

S21Matrix S21Matrix::Minor(int col_index, int row_index) const {
  S21Matrix tmp(rows_ - 1, cols_ - 1);
  for (int i = 0; i < tmp.rows_; i++) {
    for (int j = 0; j < tmp.cols_; j++) {
      if (j < col_index && i < row_index) tmp.matrix_[i][j] = matrix_[i][j];
      if (j >= col_index && i < row_index)
        tmp.matrix_[i][j] = matrix_[i][j + 1];
      if (j < col_index && i >= row_index)
        tmp.matrix_[i][j] = matrix_[i + 1][j];
      if (j >= col_index && i >= row_index)
        tmp.matrix_[i][j] = matrix_[i + 1][j + 1];
    }
  }
  return tmp;
}
