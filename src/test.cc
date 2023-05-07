#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Constructors, def_cons) {
  S21Matrix tmp;
  EXPECT_EQ(tmp.GetRows(), 0);
  EXPECT_EQ(tmp.GetCols(), 0);
}

TEST(Constructors, exception_con) {
  S21Matrix exception(1, 1);
  EXPECT_ANY_THROW(exception(1, 2));
}

TEST(Constructors, exception_con_neg) {
  S21Matrix exception(1, 1);
  EXPECT_ANY_THROW(exception(1, -2));
}

TEST(Constructors, exception_con_neg2) {
  S21Matrix exception(1, 1);
  EXPECT_ANY_THROW(exception(-1, 2));
}

TEST(Constructors, par_con) {
  S21Matrix tmp(2, 3);
  EXPECT_EQ(tmp.GetRows(), 2);
  EXPECT_EQ(tmp.GetCols(), 3);
}

TEST(Constructors, par_cos_exc) {
  EXPECT_ANY_THROW(S21Matrix exception(0, -2));
}

TEST(Constructors, copy_con) {
  S21Matrix tmp(2, 3);
  S21Matrix result(tmp);
  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 3);
  EXPECT_EQ(tmp == result, true);
}

TEST(Constructors, copy_con_br) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a = b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(Constructors, move_con) {
  S21Matrix tmp(2, 3);
  S21Matrix result(std::move(tmp));
  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 3);
}

TEST(Constructors, par_con_exc) {
  S21Matrix exception(1, 1);
  EXPECT_ANY_THROW(exception(5, 0) = 5);
}

TEST(Eq, bool1) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(Eq, bool) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(2, 2);
  ASSERT_FALSE(matrix_a == matrix_b);
}

TEST(Sum, 1) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SumMatrix(b));
}

TEST(Sum, 2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a.SumMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 3.3);
}

TEST(Sum, 3) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;
  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;
  matrix_a.SumMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}

TEST(Sum, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;
  EXPECT_THROW(matrix_a.SumMatrix(matrix_b), std::out_of_range);
}

TEST(Sub, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;
  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;
  matrix_a.SubMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}

TEST(Sub, 2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a.SubMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), -1.1);
}

TEST(Sub, 3) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SubMatrix(b));
}

TEST(Sub, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;
  EXPECT_THROW(matrix_a.SubMatrix(matrix_b), std::out_of_range);
}

TEST(MulN, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;
  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;
  matrix_a.MulNumber(10);
  ASSERT_TRUE(matrix_a == result);
}

TEST(MulN, 2) {
  S21Matrix a(3, 2);
  a(1, 1) = 1.1;
  S21Matrix result = a * 2;
  EXPECT_DOUBLE_EQ(result(1, 1), 2.2);
}

TEST(MulN, 3) {
  S21Matrix a(3, 2);
  a(1, 1) = 1.1;
  a *= 2;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(MulN, 4) {
  S21Matrix a(3, 2);
  a(1, 1) = 1.1;
  a.MulNumber(2);
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(MulN, 5) {
  S21Matrix a(3, 2);
  a.MulNumber(NAN);
  EXPECT_EQ(std::isnan(a(1, 1)), 1);
  EXPECT_EQ(std::isnan(a(2, 1)), 1);
  EXPECT_EQ(std::isnan(a(1, 0)), 1);
}

TEST(MulN, 6) {
  S21Matrix a(3, 2);
  a(1, 1) = 228;
  a.MulNumber(2);
  EXPECT_DOUBLE_EQ(a(1, 1), 456);
}

TEST(MulN, 7) {
  S21Matrix a(3, 2);
  a(1, 1) = -7;
  a.MulNumber(2);
  EXPECT_DOUBLE_EQ(a(1, 1), -14);
}

TEST(MulN, 8) {
  S21Matrix a(3, 2);
  a(1, 1) = 1.1;
  a.MulNumber(0);
  EXPECT_DOUBLE_EQ(a(1, 1), 0);
}

TEST(MulN, 9) {
  S21Matrix a(3, 3);
  a(1, 1) = 1.1;
  a.MulNumber(2);
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(MulM, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;
  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;
  matrix_a.MulMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}

TEST(MulM, 2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.MulMatrix(b));
}

TEST(MulM, false1) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6.6;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;
  EXPECT_THROW(matrix_a.MulMatrix(matrix_b), std::out_of_range);
}

TEST(MulM, false2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(S21Matrix result = a * b);
}

TEST(Transpose, 1) {
  S21Matrix matrix_a(4, 3);
  S21Matrix result(3, 4);
  matrix_a(0, 0) = 7;
  matrix_a(0, 1) = -98;
  matrix_a(0, 2) = 0.5;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 5.4;
  matrix_a(1, 2) = 32;
  matrix_a(2, 0) = 3.12;
  matrix_a(2, 1) = 2323;
  matrix_a(2, 2) = 23;
  matrix_a(3, 0) = -78;
  matrix_a(3, 1) = 476.4;
  matrix_a(3, 2) = 21;
  result(0, 0) = 7;
  result(0, 1) = 0;
  result(0, 2) = 3.12;
  result(0, 3) = -78;
  result(1, 0) = -98;
  result(1, 1) = 5.4;
  result(1, 2) = 2323;
  result(1, 3) = 476.4;
  result(2, 0) = 0.5;
  result(2, 1) = 32;
  result(2, 2) = 23;
  result(2, 3) = 21;
  S21Matrix res = matrix_a.Transpose();
  ASSERT_TRUE(res == result);
}

TEST(Transpose, 2) {
  S21Matrix result(2, 2);
  result(0, 0) = 1;
  result(0, 1) = 2;
  result(1, 0) = 4;
  result(1, 1) = 3;
  result = result.Transpose();
  EXPECT_EQ(result(0, 0), 1);
  EXPECT_EQ(result(0, 1), 4);
  EXPECT_EQ(result(1, 0), 2);
  EXPECT_EQ(result(1, 1), 3);
}

TEST(Inverse, 1x1) {
  S21Matrix tmp(1, 1);
  tmp(0, 0) = 20;
  S21Matrix res = tmp.InverseMatrix();
  EXPECT_EQ(res(0, 0), 0.05);
}

TEST(Inverse, 1x1_2) {
  S21Matrix tmp(1, 1);
  tmp(0, 0) = 100;
  S21Matrix res = tmp.InverseMatrix();
  EXPECT_EQ(res(0, 0), 0.01);
}

TEST(Inverse, 1) {
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 3);
  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;
  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;
  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;
  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;
  matrix_a = matrix_a.InverseMatrix();
  ASSERT_TRUE(matrix_a.EqMatrix(result));
  S21Matrix matrix_b(3, 3);
  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(0, 2) = 3;
  matrix_b(1, 0) = 4;
  matrix_b(1, 1) = 5;
  matrix_b(1, 2) = 6;
  matrix_b(2, 0) = 7;
  matrix_b(2, 1) = 8;
  matrix_b(2, 2) = 9;
  EXPECT_THROW(matrix_b.InverseMatrix(), std::out_of_range);
}

TEST(Inverse, 2) {
  S21Matrix basic(3, 3);
  basic(0, 0) = 4;
  basic(0, 1) = -2;
  basic(0, 2) = 1;
  basic(1, 0) = 1;
  basic(1, 1) = 6;
  basic(1, 2) = -2;
  basic(2, 0) = 1;
  basic(2, 1) = 0;
  basic(2, 2) = 0;
  basic = basic.InverseMatrix();
  EXPECT_EQ(basic(0, 1), 0);
  EXPECT_EQ(basic(0, 2), 1);
  EXPECT_EQ(basic(1, 0), 1);
  EXPECT_EQ(basic(2, 0), 3);
  EXPECT_EQ(basic(2, 1), 1);
  EXPECT_EQ(basic(2, 2), -13);
}

TEST(Inverse, 3) {
  S21Matrix basic(3, 3);
  basic(0, 0) = 2;
  basic(0, 1) = 2;
  basic(0, 2) = 123;
  basic(1, 0) = 12;
  basic(1, 1) = 6;
  basic(1, 2) = 5;
  basic(2, 0) = 1;
  basic(2, 1) = 2;
  basic(2, 2) = 8;
  basic = basic.InverseMatrix();
  EXPECT_DOUBLE_EQ(basic(0, 1), 0.10910815939278938);
  EXPECT_DOUBLE_EQ(basic(0, 2), -0.34535104364326374);
  EXPECT_DOUBLE_EQ(basic(1, 0), -0.043168880455407968);
  EXPECT_DOUBLE_EQ(basic(2, 0), 0.0085388994307400382);
  EXPECT_DOUBLE_EQ(basic(2, 1), -0.00094876660341555979);
  EXPECT_DOUBLE_EQ(basic(2, 2), -0.0056925996204933585);
}

TEST(Inverse, 4) {
  S21Matrix exception(3, 3);
  exception(0, 0) = 1;
  exception(0, 1) = 4;
  exception(0, 2) = 1;
  exception(1, 0) = 3;
  exception(1, 1) = 7;
  exception(1, 2) = 2;
  exception(2, 0) = 3;
  exception(2, 1) = 2;
  exception(2, 2) = 1;
  EXPECT_ANY_THROW(exception.InverseMatrix());
}
TEST(Inverse, 5) {
  S21Matrix exception(2, 2);
  exception(0, 0) = 92;
  exception(0, 1) = 92;
  exception(1, 0) = 92;
  exception(1, 1) = 92;
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(Inverse, 6) {
  S21Matrix tmp(4, 4);
  tmp(0, 0) = 23;
  tmp(0, 1) = 10;
  tmp(0, 2) = 5;
  tmp(0, 3) = 0;
  tmp(1, 0) = 51;
  tmp(1, 1) = 54;
  tmp(1, 2) = 1;
  tmp(1, 3) = 0.2;
  tmp(2, 0) = 0;
  tmp(2, 1) = 1;
  tmp(2, 2) = -1;
  tmp(2, 3) = -1;
  tmp(3, 0) = -1;
  tmp(3, 1) = 1;
  tmp(3, 2) = 1;
  tmp(3, 3) = 1;

  S21Matrix res(4, 4);
  res(0, 0) = -0.00217;
  res(0, 1) = 0.01358;
  res(0, 2) = -0.35452;
  res(0, 3) = -0.35724;
  res(1, 0) = -0.00109;
  res(1, 1) = 0.00679;
  res(1, 2) = 0.32274;
  res(1, 3) = 0.32138;
  res(2, 0) = 0.21217;
  res(2, 1) = -0.07607;
  res(2, 2) = 0.98533;
  res(2, 3) = 1.00054;
  res(3, 0) = -0.21326;
  res(3, 1) = 0.08286;
  res(3, 2) = -1.66259;
  res(3, 3) = -0.67916;
  S21Matrix inv = tmp.InverseMatrix();
  ASSERT_TRUE(inv == res);
}

TEST(Inverse, False) {
  S21Matrix matrix_a(4, 3);
  S21Matrix result(3, 4);
  matrix_a(0, 0) = 7;
  matrix_a(0, 1) = -98;
  matrix_a(0, 2) = 0.5;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 5.4;
  matrix_a(1, 2) = 32;
  matrix_a(2, 0) = 3.12;
  matrix_a(2, 1) = 2323;
  matrix_a(2, 2) = 23;
  matrix_a(3, 0) = -78;
  matrix_a(3, 1) = 476.4;
  matrix_a(3, 2) = 21;
  EXPECT_THROW(matrix_a.InverseMatrix(), std::out_of_range);
}

TEST(OperatorPlus, 1) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  S21Matrix result = a + b;
  EXPECT_DOUBLE_EQ(result(1, 1), 3.3);
}

TEST(OperatorPlus, 2) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;
  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;
  ASSERT_TRUE((matrix_a + matrix_b) == result);
}

TEST(OperatorPlus, 3) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(S21Matrix result = a + b);
}

TEST(OperatorMinus, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;
  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;
  ASSERT_TRUE((matrix_a - matrix_b) == result);
}

TEST(OperatorMinus, 2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  S21Matrix result = a - b;
  EXPECT_DOUBLE_EQ(result(1, 1), -1.1);
}

TEST(OperatorMinus, False) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(S21Matrix result = a - b);
}

TEST(OperatorMulMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;
  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;

  ASSERT_TRUE((matrix_a * matrix_b) == result);
}

TEST(OperatorMulNumber, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;
  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;
  ASSERT_TRUE((matrix_a * 10) == result);
}

TEST(OperatorMulNumber, 2) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;
  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;
  ASSERT_TRUE((10 * matrix_a) == result);
}

TEST(OperatorSumEquel, 1) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a += b;
  EXPECT_DOUBLE_EQ(a(1, 1), 3.3);
}

TEST(OperatorSumEquel, 2) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;
  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;
  matrix_a += matrix_b;
  ASSERT_TRUE(matrix_a == result);
}

TEST(OperatorSumEquel, 3) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a += b);
}

TEST(OperatorSumEquel, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;
  EXPECT_THROW((matrix_a += matrix_b), std::out_of_range);
}

TEST(OperatorSubEquel, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;
  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;
  matrix_a -= matrix_b;
  ASSERT_TRUE(matrix_a == result);
}

TEST(OperatorSubEquel, 2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a -= b;
  EXPECT_DOUBLE_EQ(a(1, 1), -1.1);
}

TEST(OperatorSubEquel, 3) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a -= b);
}

TEST(OperatorSubEquel, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;
  EXPECT_THROW(matrix_a -= matrix_b, std::out_of_range);
}

TEST(OperatorMulMatrixEquel, 1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;
  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;
  matrix_a *= matrix_b;
  ASSERT_TRUE(matrix_a == result);
}

TEST(OperatorMulMatrixEquel, 2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a *= b);
}

TEST(OperatorMulMatrixEquel, False) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6.6;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;
  EXPECT_THROW(matrix_a *= matrix_b, std::out_of_range);
}

TEST(OperatorMulNumberEquel, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;
  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;
  matrix_a *= 10;
  ASSERT_TRUE(matrix_a == result);
}

TEST(OperatorEqMatrix, 1) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(1, 3);
  matrix_a = matrix_b;
  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(OperatorEqMatrix, 2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  EXPECT_EQ(a == b, false);
  b.SetCols(3);
  a(1, 1) = 1.3;
  b(1, 1) = 1.3;
  EXPECT_EQ(a == b, true);
  b(1, 2) = 1.3;
  EXPECT_EQ(a == b, false);
}

TEST(OperatorEqMatrix, 3) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  EXPECT_EQ(a == b, true);
  a(1, 1) = 1.3;
  EXPECT_EQ(a == b, false);
  b(1, 1) = 1.3;
  EXPECT_EQ(a == b, true);
}

TEST(Operator, True) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  ASSERT_EQ(matrix_a(0, 1), 2);
}
TEST(Operator, False) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  ASSERT_NE(matrix_a(0, 1), 19);
}

TEST(Operator, brakets) {
  S21Matrix basic(2, 3);
  basic(1, 1) = 3;
  EXPECT_EQ(basic(1, 1), 3);
}

TEST(Operator, brakets_2) {
  S21Matrix basic(12, 3);
  basic(11, 1) = 223;
  EXPECT_EQ(basic(11, 1), 223);
}

TEST(Operator, brackets_Exception) {
  S21Matrix exception(2, 3);
  EXPECT_ANY_THROW(exception(1, 5));
}

TEST(GetSet, set_rows_0) {
  S21Matrix basic(5, 5);
  S21Matrix tmp(4, 5);
  S21Matrix tmp2(4, 4);
  EXPECT_THROW(basic.SetRows(0), std::out_of_range);
  EXPECT_THROW(basic.SetCols(0), std::out_of_range);
  basic.SetRows(4);
  ASSERT_TRUE(basic == tmp);
  basic.SetCols(4);
  ASSERT_TRUE(basic == tmp2);
}

TEST(GetSet, set_zero_Matrix) {
  S21Matrix basic;
  EXPECT_EQ(basic.GetRows(), 0);
  EXPECT_EQ(basic.GetCols(), 0);
}

TEST(GetSet, int_eq) {
  S21Matrix basic(2, 2);
  EXPECT_EQ(basic.GetRows(), 2);
  EXPECT_EQ(basic.GetCols(), 2);
}

TEST(GetSet, True) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;
  ASSERT_EQ(matrix_a.GetRows(), 3);
  ASSERT_EQ(matrix_a.GetCols(), 3);
}

TEST(GetSet, set_rows) {
  S21Matrix basic(2, 3);
  basic(1, 1) = 2.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic.GetRows(), 2);
  EXPECT_EQ(basic.GetCols(), 3);
  basic.SetRows(4);
  basic(3, 2) = 1.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic(3, 2), 1.2);
  EXPECT_EQ(basic.GetRows(), 4);
  EXPECT_EQ(basic.GetCols(), 3);
}

TEST(GetSet, set_cols) {
  S21Matrix basic(2, 3);
  basic(1, 1) = 2.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic.GetRows(), 2);
  EXPECT_EQ(basic.GetCols(), 3);
  basic.SetCols(5);
  basic(1, 4) = 1.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic(1, 4), 1.2);
  EXPECT_EQ(basic.GetRows(), 2);
  EXPECT_EQ(basic.GetCols(), 5);
}

TEST(throw, 1) {
  S21Matrix A(1, 1);
  EXPECT_THROW(A(2, 2) = 2, std::out_of_range);
}

TEST(throw, 2) {
  S21Matrix A(1, 1);
  A(0, 0) = 1;
  S21Matrix B(1, 1);
  B(0, 0) = -1;
  ASSERT_FALSE(A == B);
}

TEST(throw, 3) {
  S21Matrix A;
  EXPECT_THROW(A.Transpose(), std::out_of_range);
}

TEST(throw, 4) {
  S21Matrix A(1, 1);
  A(0, 0) = 2;
  S21Matrix B(1, 1);
  B(0, 0) = 0.5;
  ASSERT_TRUE(A.InverseMatrix() == B);
}

TEST(throw, 5) {
  S21Matrix A;
  EXPECT_THROW(A.CalcComplements(), std::out_of_range);
}

TEST(throw, 6) {
  S21Matrix A(1, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  EXPECT_THROW(A.CalcComplements(), std::out_of_range);
}

TEST(throw, 7) {
  S21Matrix A(1, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  S21Matrix B;
  EXPECT_THROW(A.MulMatrix(B), std::out_of_range);
}

TEST(throw, 8) {
  S21Matrix A;
  EXPECT_THROW(A.MulNumber(5), std::out_of_range);
}

TEST(throw, 9) {
  S21Matrix A, B;
  EXPECT_THROW(A.SubMatrix(B), std::out_of_range);
}

TEST(throw, 10) {
  S21Matrix A, B;
  EXPECT_THROW(A.SumMatrix(B), std::out_of_range);
}

TEST(throw, 11) {
  S21Matrix A;
  EXPECT_THROW(A.InverseMatrix(), std::out_of_range);
}

TEST(throw, 12) { EXPECT_THROW(S21Matrix A(0, 1), std::out_of_range); }

TEST(throw, 13) { EXPECT_THROW(S21Matrix A(1, 0), std::out_of_range); }

TEST(throw, 14) { EXPECT_THROW(S21Matrix A(-1, 120), std::out_of_range); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
