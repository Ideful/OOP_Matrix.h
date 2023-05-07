#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_
#include <cmath>
#include <cstdio>
#include <iostream>

class S21Matrix {
 public:
  //  methods + base
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();
  int GetRows()const noexcept;
  int GetCols()const noexcept;
  void SetRows(int rows);
  void SetCols(int cols);

  //  operations
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  S21Matrix InverseMatrix() const;
  double Determinant() const;

  //  operators
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  friend S21Matrix operator*(double value, const S21Matrix& other);
  friend S21Matrix operator*(const S21Matrix& other, double value);
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const S21Matrix& other);
  void operator*=(double value);
  double& operator()(int i, int j) const;
  bool operator==(const S21Matrix& other) const noexcept;

 private:
  int rows_, cols_;
  double** matrix_;
  S21Matrix Minor(int col_index, int row_index) const;
  void Desctructor();
  void Constructor(int rows, int cols);
  void Cpy(const S21Matrix& other);

};

#endif  // S21_MATRIX_OOP_H_