#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (cols < 1 || rows < 1) {
    throw std::out_of_range("Incorrect input");
  } else {
    rows_ = rows;
    cols_ = cols;
    Constructor(rows_, cols_);
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
  
  
  
// S21Matrix result(std::move(tmp));
S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.cols_ = 0;
  other.rows_ = 0;
}

S21Matrix::~S21Matrix() { Desctructor(); }

// ######################################################################

void S21Matrix::Constructor(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  if (rows >= 0 && cols >= 0) {
    matrix_ = new double*[rows];
    for (int i = 0; i < rows; ++i) {
      matrix_[i] = new double[cols]();
    }
  }
}

void S21Matrix::Desctructor() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}

void S21Matrix::Cpy(const S21Matrix& other) {
  Desctructor();
  Constructor(other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

int S21Matrix::GetCols() const noexcept { return cols_; }

int S21Matrix::GetRows() const noexcept { return rows_; }

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) {
    throw std::out_of_range("Incorrect input");
  } else {
    S21Matrix tmp(rows_, cols);
    double max = cols > cols_ ? cols_ : cols;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < max; j++) {
        tmp.matrix_[i][j] = matrix_[i][j];
      }
    }
    Cpy(tmp);
  }
}

void S21Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::out_of_range("Incorrect input");
  } else {
    S21Matrix tmp(rows, cols_);
    double max = rows > rows_ ? rows_ : rows;
    for (int i = 0; i < max; i++) {
      for (int j = 0; j < cols_; j++) {
        tmp.matrix_[i][j] = matrix_[i][j];
      }
    }
    Cpy(tmp);
  }
}