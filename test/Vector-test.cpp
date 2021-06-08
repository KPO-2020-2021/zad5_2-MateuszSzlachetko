#include "gtest/gtest.h"
#include "Vector.h"

TEST(Vector, constructor_empty)
{
    Vector<double, 2> v1;
    Vector<double, 2> v2({0, 0});
    Vector<double, 2> v3 = {0, 0};
    Vector<double, 5> v4;
    Vector<double, 5> v5 = {0, 0, 0, 0, 0};

    EXPECT_EQ(v1, v2);
    EXPECT_EQ(v1, v3);
    EXPECT_EQ(v4, v5);
}

TEST(Vector, constructor_initializer_list)
{
    Vector<double, 2> v1({1, -13});
    Vector<double, 2> v2({5, 2.222});
    Vector<double, 3> v3({66, 714, -0.54});
    Vector<double, 8> v4({1, 2, 3, 4, 5, 6, 7, 8});

    EXPECT_EQ(v1, (Vector<double, 2>({1, -13})));
    EXPECT_EQ(v2, (Vector<double, 2>({5, 2.222})));
    EXPECT_EQ(v3, (Vector<double, 3>({66, 714, -0.54})));
    EXPECT_EQ(v4, (Vector<double, 8>({1, 2, 3, 4, 5, 6, 7, 8})));
}

TEST(Vector, constructor_std_vector)
{
    std::vector<double> v_1 = {1, -13};
    std::vector<double> v_2 = {5, 2.222};
    std::vector<double> v_3 = {66, 714, -0.54};
    std::vector<double> v_4 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<double> v_testthrow = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    Vector<double, 2> v1(v_1);
    Vector<double, 2> v2(v_2);
    Vector<double, 3> v3(v_3);
    Vector<double, 8> v4(v_4);

    EXPECT_EQ(v1, (Vector<double, 2>({1, -13})));
    EXPECT_EQ(v2, (Vector<double, 2>({5, 2.222})));
    EXPECT_EQ(v3, (Vector<double, 3>({66, 714, -0.54})));
    EXPECT_EQ(v4, (Vector<double, 8>({1, 2, 3, 4, 5, 6, 7, 8})));

    EXPECT_THROW((Vector<double, 8>(v_testthrow)), std::invalid_argument);
    EXPECT_THROW((Vector<double, 3>(v_2)), std::invalid_argument);
}

TEST(Vector, Addition)
{
    Vector<double, 3> v1({1, 1, 1});
    Vector<double, 3> v2({15, 1, 4});
    Vector<double, 3> result1;

    result1 = v1 + v2;

    EXPECT_EQ(result1, (Vector<double, 3>({16, 2, 5})));

    Vector<double, 4> v3({0, -15, 77, 3});
    Vector<double, 4> v4({0.25, 3, 22, 7});
    Vector<double, 4> result2;

    result2 = v3 + v4;

    EXPECT_EQ(result2, (Vector<double, 4>({0.25, -12, 99, 10})));

    Vector<double, 5> v5({4, 0, 9, -777, 1});
    Vector<double, 5> v6({12, -0.123, 22, 1, 99});
    Vector<double, 5> result3;

    result3 = v5 + v6;

    EXPECT_EQ(result3, (Vector<double, 5>({16, -0.123, 31, -776, 100})));
}

TEST(Vector, Subtraction)
{
    Vector<double, 3> v1({1, 1, 1});
    Vector<double, 3> v2({15, 1, 4});
    Vector<double, 3> result1;

    result1 = v1 - v2;

    EXPECT_EQ(result1, (Vector<double, 3>({-14, 0, -3})));

    Vector<double, 4> v3({0, -15, 77, 3});
    Vector<double, 4> v4({0.25, 3, 22, 7});
    Vector<double, 4> result2;

    result2 = v3 - v4;

    EXPECT_EQ(result2, (Vector<double, 4>({-0.25, -18, 55, -4})));

    Vector<double, 5> v5({4, 0, 9, -777, 1});
    Vector<double, 5> v6({12, -0.123, 1, 22, 99});
    Vector<double, 5> result3;

    result3 = v5 - v6;

    EXPECT_EQ(result3, (Vector<double, 5>({-8, 0.123, 8, -799, -98})));
}

TEST(Vector, Division_vector_product)
{
    Vector<double, 3> v1({1, 1, 1});
    Vector<double, 3> v2;

    v2 = v1 / 5;

    EXPECT_EQ(v2, (Vector<double, 3>({0.2, 0.2, 0.2})));

    Vector<double, 4> v3({2, 1, -0.8, 0});
    Vector<double, 4> v4;

    v4 = v3 / 1;

    EXPECT_EQ(v4, (Vector<double, 4>({2, 1, -0.8, 0})));

    EXPECT_THROW(v3 / 0, std::invalid_argument);
}

TEST(Vector, Multiplication_scalar_product)
{
    Vector<double, 3> v1({1, 1, 1});
    Vector<double, 3> v2({15, 1, 4});
    double result1;

    result1 = v1 * v2;

    EXPECT_EQ(result1, 20);

    result1 = v2 * v1;

    EXPECT_EQ(result1, 20);

    Vector<double, 4> v3({2, 1, -0.8, 0});
    Vector<double, 4> v4({15, 3.333, 4, 155555});
    double result2;

    result2 = v3 * v4;

    EXPECT_EQ(result2, 30.133);

    result2 = v3 * v4;

    EXPECT_EQ(result2, 30.133);
}

TEST(Vector, Multiplication_vector_product)
{
    Vector<double, 3> v1({1, 1, 1});
    double scalar = 5;
    Vector<double, 3> result1;

    result1 = v1 * scalar;

    EXPECT_EQ(result1, (Vector<double, 3>({5, 5, 5})));

    Vector<double, 3> v2({0, -5, 2});
    scalar = 15;
    Vector<double, 3> result2;

    result2 = v2 * scalar;

    EXPECT_EQ(result2, (Vector<double, 3>({0, -75, 30})));

    Vector<double, 2> v3({1, -4});
    scalar = 3;
    Vector<double, 2> result3;

    result3 = v3 * scalar;

    EXPECT_EQ(result3, (Vector<double, 2>({3, -12})));

    Vector<double, 4> v4({1, -4, 2.25, -3.1});
    scalar = 2.2;
    Vector<double, 4> result4;

    result4 = v4 * scalar;

    EXPECT_EQ(result4, (Vector<double, 4>({2.2, -8.8, 4.95, -6.82})));
}

TEST(Vector, Length)
{
    Vector<double, 3> v1({1, 1, 1});
    Vector<double, 3> v2({15, 1, 4});
    Vector<double, 4> v3({0, 4, 3, 0});
    Vector<double, 2> v4({1.222, -8});
    Vector<double, 5> v5({0.55, 1, 1, 4, 8});
    double length;

    length = v1.Length();

    EXPECT_EQ(length, sqrt(1 + 1 + 1));

    length = v2.Length();

    EXPECT_EQ(length, sqrt(225 + 1 + 16));

    length = v3.Length();

    EXPECT_EQ(length, sqrt(16 + 9));

    length = v4.Length();

    EXPECT_EQ(length, sqrt(65.493284));

    length = v5.Length();

    EXPECT_EQ(length, sqrt(82.3025));
}

TEST(Vector, print)
{
    std::stringstream stream;
    Vector<double, 3> v1({1, 1, 1});
    Vector<double, 6> v2({1, 1, 5, 7, -10, 0});
    Vector<double, 4> v3({-0.231, 0.5666, 1, 15});

    stream << v1;

    EXPECT_EQ(stream.str(), "1\t1\t1");
    stream.str(std::string());

    stream << v2;

    EXPECT_EQ(stream.str(), "1\t1\t5\t7\t-10\t0");
    stream.str(std::string());

    stream << v3;

    EXPECT_EQ(stream.str(), "-0.231\t0.5666\t1\t15");
    stream.str(std::string());
}

TEST(Vector, read)
{
    std::stringstream stream;
    Vector<double, 3> v1;
    Vector<double, 3> test1({1, 15, 0});

    stream << "1 15 0\n";
    stream >> v1;
    EXPECT_EQ(v1, test1);

    Vector<double, 4> v2;
    Vector<double, 4> test2({10.000236, -15.555, 2137, 0.00006});

    stream << "10.000236 -15.555 2137 0.00006\n";
    stream >> v2;
    EXPECT_EQ(v2, test2);

    Vector<int, 8> v3;
    Vector<int, 8> test3({1, 2, 3, 4, 5, 6, 7, 8});

    stream << "1 2 3 4 5 6 7 8\n";
    stream >> v3;
    EXPECT_EQ(v3, test3);
}

TEST(Vector, index_operator)
{
    Vector<double, 2> v1;

    EXPECT_EQ(v1[0], 0);
    EXPECT_EQ(v1[1], 0);
    EXPECT_THROW(v1[-1], std::invalid_argument);
    EXPECT_THROW(v1[2], std::invalid_argument);

    Vector<double, 3> v2({15, 222, 0.55});

    EXPECT_EQ(v2[0], 15);
    EXPECT_EQ(v2[1], 222);
    EXPECT_EQ(v2[2], 0.55);
    EXPECT_THROW(v2[-1], std::invalid_argument);
    EXPECT_THROW(v2[-5], std::invalid_argument);
    EXPECT_THROW(v2[15], std::invalid_argument);
    EXPECT_THROW(v2[3], std::invalid_argument);
    EXPECT_THROW(v2[4], std::invalid_argument);
    EXPECT_THROW(v2[8], std::invalid_argument);

    Vector<double, 6> v3({0, 16, 49, -15, 2.333, 0});

    EXPECT_EQ(v3[0], 0);
    EXPECT_EQ(v3[1], 16);
    EXPECT_EQ(v3[2], 49);
    EXPECT_EQ(v3[3], -15);
    EXPECT_EQ(v3[4], 2.333);
    EXPECT_EQ(v3[5], 0);
    EXPECT_THROW(v2[-1], std::invalid_argument);
    EXPECT_THROW(v2[-5], std::invalid_argument);
    EXPECT_THROW(v2[15], std::invalid_argument);
    EXPECT_THROW(v2[6], std::invalid_argument);
}

TEST(Vector, index_operator_set)
{
    Vector<double, 2> v1;

    EXPECT_EQ(v1[0], 0);
    EXPECT_EQ(v1[1], 0);

    v1[0] = 5;
    EXPECT_EQ(v1[0], 5);
    EXPECT_EQ(v1[1], 0);

    Vector<double, 3> v2({15, 222, 0.55});

    EXPECT_EQ(v2[0], 15);
    EXPECT_EQ(v2[1], 222);
    EXPECT_EQ(v2[2], 0.55);

    v2[0] = 0;
    v2[1] = 0;
    v2[2] = 0;

    EXPECT_EQ(v2[0], 0);
    EXPECT_EQ(v2[1], 0);
    EXPECT_EQ(v2[2], 0);
    EXPECT_THROW(v2[3] = 0, std::invalid_argument);
    EXPECT_THROW(v2[-1] = 0, std::invalid_argument);
}