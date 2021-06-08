#include "gtest/gtest.h"
#include "Matrix.h"

TEST(Matrix, constructor_empty)
{
    Matrix<double, 1> m1;
    Matrix<double, 1> m2({Vector<double, 1>({0})});

    EXPECT_EQ(m1, m2);

    Matrix<double, 2> m3;
    Matrix<double, 2> m4({Vector<double, 2>(), Vector<double, 2>()});

    EXPECT_EQ(m3, m4);

    Matrix<double, 3> m5;
    Matrix<double, 3> m6({Vector<double, 3>(), Vector<double, 3>(), Vector<double, 3>()});

    EXPECT_EQ(m5, m6);
}

TEST(Matrix, constructor_initializer_list_Vectors)
{
    Matrix<double, 1> m1({Vector<double, 1>({1})});
    Matrix<double, 2> m2({Vector<double, 2>({15, 14}), Vector<double, 2>({-5, 6})});
    Matrix<double, 3> m3({Vector<double, 3>({88, -6.6, 0}), Vector<double, 3>({1118, 2.69, -5.11}), Vector<double, 3>({18, 226, -4})});

    EXPECT_EQ(m1, (Matrix<double, 1>({Vector<double, 1>({1})})));
    EXPECT_EQ(m2, (Matrix<double, 2>({Vector<double, 2>({15, 14}), Vector<double, 2>({-5, 6})})));
    EXPECT_EQ(m3, (Matrix<double, 3>({Vector<double, 3>({88, -6.6, 0}), Vector<double, 3>({1118, 2.69, -5.11}), Vector<double, 3>({18, 226, -4})})));
}

TEST(Matrix, constructor_initializer_list_values)
{
    Matrix<double, 1> m1({1});
    Matrix<double, 2> m2({15, 14, -5, 6});
    Matrix<double, 3> m3({88, -6.6, 0, 1118, 2.69, -5.11, 18, 226, -4});

    EXPECT_EQ(m1, (Matrix<double, 1>({Vector<double, 1>({1})})));
    EXPECT_EQ(m2, (Matrix<double, 2>({Vector<double, 2>({15, 14}), Vector<double, 2>({-5, 6})})));
    EXPECT_EQ(m3, (Matrix<double, 3>({Vector<double, 3>({88, -6.6, 0}), Vector<double, 3>({1118, 2.69, -5.11}), Vector<double, 3>({18, 226, -4})})));
}

TEST(Matrix, Matrix_Vector_multiplication)
{
    Matrix<double, 3> m1({Vector<double, 3>({1, 1, 1}), Vector<double, 3>({1, 1, 1}), Vector<double, 3>({1, 1, 1})});
    Vector<double, 3> v1({1, 1, 1});
    Vector<double, 3> v2({3, 3, 3});
    EXPECT_EQ(m1 * v1, v2);

    Matrix<double, 3> m2({Vector<double, 3>({1, 2, 1}), Vector<double, 3>({1, 4, 1}), Vector<double, 3>({1, 5, 1})});
    Vector<double, 3> v3({1, 2, 0});
    Vector<double, 3> v4({5, 9, 11});
    EXPECT_EQ(m2 * v3, v4);

    Matrix<double, 4> m3({Vector<double, 4>({1, 2, 1, 5}), Vector<double, 4>({1, 4, 1, 2}), Vector<double, 4>({1, 5, 1, 1}), Vector<double, 4>({22, 5.5, -7, 0})});
    Vector<double, 4> v5({1, 2, -4, 2.2});
    Vector<double, 4> v6({12, 9.4, 9.2, 61});
    EXPECT_EQ(m3 * v5, v6);
}

TEST(Matrix, Matrix_Matrix_multiplication)
{
    Matrix<double, 2> m1({Vector<double, 2>({1, 0}), Vector<double, 2>({0, 1})});
    Matrix<double, 2> m2({Vector<double, 2>({1, 2}), Vector<double, 2>({3, 4})});
    Matrix<double, 2> m3;

    m3 = m1 * m2;

    EXPECT_EQ(m3, m2);

    Matrix<double, 3> m4({Vector<double, 3>({3, 2, 0}), Vector<double, 3>({2, 1, 3}), Vector<double, 3>({1, 1, 2})});
    Matrix<double, 3> m5({Vector<double, 3>({2, 0, 2}), Vector<double, 3>({-5, 2, 1}), Vector<double, 3>({2.5, 3, 3})});
    Matrix<double, 3> m6({Vector<double, 3>({-4, 4, 8}), Vector<double, 3>({6.5, 11, 14}), Vector<double, 3>({2, 8, 9})});
    Matrix<double, 3> result1;
    result1 = m4 * m5;

    EXPECT_EQ(result1, m6);

    Matrix<double, 6> m7({Vector<double, 6>({1, 0, 0, 0, 0, 0}),
                          Vector<double, 6>({0, 1, 0, 0, 0, 0}),
                          Vector<double, 6>({0, 0, 1, 0, 0, 0}),
                          Vector<double, 6>({0, 0, 0, 1, 0, 0}),
                          Vector<double, 6>({0, 0, 0, 0, 1, 0}),
                          Vector<double, 6>({0, 0, 0, 0, 0, 1})});

    Matrix<double, 6> m8({Vector<double, 6>({1, 0, 9, 0, -9, 0}),
                          Vector<double, 6>({0, 1, 0, 5, 0, 2}),
                          Vector<double, 6>({2, 0, 1, 0, 2, 0}),
                          Vector<double, 6>({14, 0, 0, 1, 0, 0}),
                          Vector<double, 6>({0, 0, 0, 16, 1, 0}),
                          Vector<double, 6>({0, 12, 0, 0, -4, 1})});
    Matrix<double, 6> result2;

    result2 = m7 * m8;

    EXPECT_EQ(result2, m8);

    result2 = m8 * m7;

    EXPECT_EQ(result2, m8);
}

TEST(Matrix, index_operator)
{
    Matrix<double, 2> m({Vector<double, 2>({2, 4}), Vector<double, 2>({-5, 6})});

    EXPECT_EQ(m[0], (Vector<double, 2>({2, 4})));
    EXPECT_EQ(m[1], (Vector<double, 2>({-5, 6})));
    EXPECT_EQ(m[0][0], 2);
    EXPECT_EQ(m[0][1], 4);
    EXPECT_EQ(m[1][0], -5);
    EXPECT_EQ(m[1][1], 6);
    EXPECT_THROW(m[-1], std::invalid_argument);
    EXPECT_THROW(m[2], std::invalid_argument);

    Matrix<double, 3> m2({Vector<double, 3>({2, 4, 1}), Vector<double, 3>({-5, 6, 0}), Vector<double, 3>({2, -9, 1})});

    EXPECT_EQ(m2[0], (Vector<double, 3>({2, 4, 1})));
    EXPECT_EQ(m2[1], (Vector<double, 3>({-5, 6, 0})));
    EXPECT_EQ(m2[2], (Vector<double, 3>({2, -9, 1})));
    EXPECT_EQ(m2[0][0], 2);
    EXPECT_EQ(m2[0][1], 4);
    EXPECT_EQ(m2[0][2], 1);
    EXPECT_EQ(m2[1][0], -5);
    EXPECT_EQ(m2[1][1], 6);
    EXPECT_EQ(m2[1][2], 0);
    EXPECT_EQ(m2[2][0], 2);
    EXPECT_EQ(m2[2][1], -9);
    EXPECT_EQ(m2[2][2], 1);
    EXPECT_THROW(m2[-1], std::invalid_argument);
    EXPECT_THROW(m2[3], std::invalid_argument);
}