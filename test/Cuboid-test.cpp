#include "gtest/gtest.h"
#include "Cuboid.h"

TEST(Cuboid, constructor_empty)
{
    Cuboid c;
    Cuboid c2;
    EXPECT_EQ(c, c2);

    EXPECT_EQ(c[0][0], 0);
    EXPECT_EQ(c[0][1], 0);
    EXPECT_EQ(c[0][2], 0);
    EXPECT_EQ(c[1][0], 0);
    EXPECT_EQ(c[1][1], 0);
    EXPECT_EQ(c[1][2], 0);
    EXPECT_EQ(c[2][0], 0);
    EXPECT_EQ(c[2][1], 0);
    EXPECT_EQ(c[2][2], 0);
    EXPECT_EQ(c[3][0], 0);
    EXPECT_EQ(c[3][1], 0);
    EXPECT_EQ(c[3][2], 0);
    EXPECT_EQ(c[4][0], 0);
    EXPECT_EQ(c[4][1], 0);
    EXPECT_EQ(c[4][2], 0);
    EXPECT_EQ(c[5][0], 0);
    EXPECT_EQ(c[5][1], 0);
    EXPECT_EQ(c[5][2], 0);
    EXPECT_EQ(c[6][0], 0);
    EXPECT_EQ(c[6][1], 0);
    EXPECT_EQ(c[6][2], 0);
    EXPECT_EQ(c[7][0], 0);
    EXPECT_EQ(c[7][1], 0);
    EXPECT_EQ(c[7][2], 0);
}

TEST(Cuboid, constructor_oposite_vertices)
{
    Cuboid c(0, 0, 0, 10, 10, 10);

    EXPECT_EQ(c[0][0], 0);
    EXPECT_EQ(c[0][1], 0);
    EXPECT_EQ(c[0][2], 0);
    EXPECT_EQ(c[1][0], 10);
    EXPECT_EQ(c[1][1], 0);
    EXPECT_EQ(c[1][2], 0);
    EXPECT_EQ(c[2][0], 0);
    EXPECT_EQ(c[2][1], 10);
    EXPECT_EQ(c[2][2], 0);
    EXPECT_EQ(c[3][0], 10);
    EXPECT_EQ(c[3][1], 10);
    EXPECT_EQ(c[3][2], 0);
    EXPECT_EQ(c[4][0], 0);
    EXPECT_EQ(c[4][1], 10);
    EXPECT_EQ(c[4][2], 10);
    EXPECT_EQ(c[5][0], 10);
    EXPECT_EQ(c[5][1], 10);
    EXPECT_EQ(c[5][2], 10);
    EXPECT_EQ(c[6][0], 0);
    EXPECT_EQ(c[6][1], 0);
    EXPECT_EQ(c[6][2], 10);
    EXPECT_EQ(c[7][0], 10);
    EXPECT_EQ(c[7][1], 0);
    EXPECT_EQ(c[7][2], 10);

    Cuboid c2(1, -1, 5, 15, 10.5, 10);
    EXPECT_EQ(c2[0], Vector3D({1, -1, 5}));
    EXPECT_EQ(c2[1], Vector3D({15, -1, 5}));
    EXPECT_EQ(c2[2], Vector3D({1, 10.5, 5}));
    EXPECT_EQ(c2[3], Vector3D({15, 10.5, 5}));
    EXPECT_EQ(c2[4], Vector3D({1, 10.5, 10}));
    EXPECT_EQ(c2[5], Vector3D({15, 10.5, 10}));
    EXPECT_EQ(c2[6], Vector3D({1, -1, 10}));
    EXPECT_EQ(c2[7], Vector3D({15, -1, 10}));
}

TEST(Cuboid, translation)
{
    Cuboid c(0, 0, 0, 10, 10, 10);
    c.Translate(Vector3D({10, 10, 10}));

    EXPECT_EQ(c[0][0], 10);
    EXPECT_EQ(c[0][1], 10);
    EXPECT_EQ(c[0][2], 10);
    EXPECT_EQ(c[1][0], 20);
    EXPECT_EQ(c[1][1], 10);
    EXPECT_EQ(c[1][2], 10);
    EXPECT_EQ(c[2][0], 10);
    EXPECT_EQ(c[2][1], 20);
    EXPECT_EQ(c[2][2], 10);
    EXPECT_EQ(c[3][0], 20);
    EXPECT_EQ(c[3][1], 20);
    EXPECT_EQ(c[3][2], 10);
    EXPECT_EQ(c[4][0], 10);
    EXPECT_EQ(c[4][1], 20);
    EXPECT_EQ(c[4][2], 20);
    EXPECT_EQ(c[5][0], 20);
    EXPECT_EQ(c[5][1], 20);
    EXPECT_EQ(c[5][2], 20);
    EXPECT_EQ(c[6][0], 10);
    EXPECT_EQ(c[6][1], 10);
    EXPECT_EQ(c[6][2], 20);
    EXPECT_EQ(c[7][0], 20);
    EXPECT_EQ(c[7][1], 10);
    EXPECT_EQ(c[7][2], 20);

    c.Translate(Vector3D({-20, -20, -20}));

    EXPECT_EQ(c[0][0], -10);
    EXPECT_EQ(c[0][1], -10);
    EXPECT_EQ(c[0][2], -10);
    EXPECT_EQ(c[1][0], 0);
    EXPECT_EQ(c[1][1], -10);
    EXPECT_EQ(c[1][2], -10);
    EXPECT_EQ(c[2][0], -10);
    EXPECT_EQ(c[2][1], 0);
    EXPECT_EQ(c[2][2], -10);
    EXPECT_EQ(c[3][0], 0);
    EXPECT_EQ(c[3][1], 0);
    EXPECT_EQ(c[3][2], -10);
    EXPECT_EQ(c[4][0], -10);
    EXPECT_EQ(c[4][1], 0);
    EXPECT_EQ(c[4][2], 0);
    EXPECT_EQ(c[5][0], 0);
    EXPECT_EQ(c[5][1], 0);
    EXPECT_EQ(c[5][2], 0);
    EXPECT_EQ(c[6][0], -10);
    EXPECT_EQ(c[6][1], -10);
    EXPECT_EQ(c[6][2], 0);
    EXPECT_EQ(c[7][0], 0);
    EXPECT_EQ(c[7][1], -10);
    EXPECT_EQ(c[7][2], 0);
}

TEST(Cuboid, Scale)
{
    Cuboid c(2, 2, 2, 10, 10, 10);
    c.Scale(2);

    EXPECT_EQ(c[0][0], 4);
    EXPECT_EQ(c[0][1], 4);
    EXPECT_EQ(c[0][2], 4);
    EXPECT_EQ(c[1][0], 20);
    EXPECT_EQ(c[1][1], 4);
    EXPECT_EQ(c[1][2], 4);
    EXPECT_EQ(c[2][0], 4);
    EXPECT_EQ(c[2][1], 20);
    EXPECT_EQ(c[2][2], 4);
    EXPECT_EQ(c[3][0], 20);
    EXPECT_EQ(c[3][1], 20);
    EXPECT_EQ(c[3][2], 4);
    EXPECT_EQ(c[4][0], 4);
    EXPECT_EQ(c[4][1], 20);
    EXPECT_EQ(c[4][2], 20);
    EXPECT_EQ(c[5][0], 20);
    EXPECT_EQ(c[5][1], 20);
    EXPECT_EQ(c[5][2], 20);
    EXPECT_EQ(c[6][0], 4);
    EXPECT_EQ(c[6][1], 4);
    EXPECT_EQ(c[6][2], 20);
    EXPECT_EQ(c[7][0], 20);
    EXPECT_EQ(c[7][1], 4);
    EXPECT_EQ(c[7][2], 20);

    c.Scale(-0.5);

    EXPECT_EQ(c[0][0], -2);
    EXPECT_EQ(c[0][1], -2);
    EXPECT_EQ(c[0][2], -2);
    EXPECT_EQ(c[1][0], -10);
    EXPECT_EQ(c[1][1], -2);
    EXPECT_EQ(c[1][2], -2);
    EXPECT_EQ(c[2][0], -2);
    EXPECT_EQ(c[2][1], -10);
    EXPECT_EQ(c[2][2], -2);
    EXPECT_EQ(c[3][0], -10);
    EXPECT_EQ(c[3][1], -10);
    EXPECT_EQ(c[3][2], -2);
    EXPECT_EQ(c[4][0], -2);
    EXPECT_EQ(c[4][1], -10);
    EXPECT_EQ(c[4][2], -10);
    EXPECT_EQ(c[5][0], -10);
    EXPECT_EQ(c[5][1], -10);
    EXPECT_EQ(c[5][2], -10);
    EXPECT_EQ(c[6][0], -2);
    EXPECT_EQ(c[6][1], -2);
    EXPECT_EQ(c[6][2], -10);
    EXPECT_EQ(c[7][0], -10);
    EXPECT_EQ(c[7][1], -2);
    EXPECT_EQ(c[7][2], -10);
}

// TEST(Cuboid, Side_length)
// {
//     Cuboid c1(2, 2, 2, 10, 10, 10);

//     std::stringstream test;
//     testing::internal::CaptureStdout();
//     c1.Side_length();
//     std::string output = testing::internal::GetCapturedStdout();

//     test << "Longer sides are equal\nFirst: 8.0000000000\nSecond: 8.0000000000\nThird: 8.0000000000\nFourth: 8.0000000000\nShorter sides are equal\nFirst: 8.0000000000\nSecond: 8.0000000000\nThird: 8.0000000000\nFourth: 8.0000000000\nVertical sides are equal\nFirst: 8.0000000000\nSecond: 8.0000000000\nThird: 8.0000000000\nFourth: 8.0000000000\n";
//     EXPECT_EQ(output, test.str());
//     test.str(std::string());

//     Cuboid c2(0, 0, 0, 100, 10, 10);

//     testing::internal::CaptureStdout();
//     c2.Side_length();
//     output = testing::internal::GetCapturedStdout();

//     test << "Longer sides are equal\nFirst: 100.0000000000\nSecond: 100.0000000000\nThird: 100.0000000000\nFourth: 100.0000000000\nShorter sides are equal\nFirst: 10.0000000000\nSecond: 10.0000000000\nThird: 10.0000000000\nFourth: 10.0000000000\nVertical sides are equal\nFirst: 10.0000000000\nSecond: 10.0000000000\nThird: 10.0000000000\nFourth: 10.0000000000\n";
//     EXPECT_EQ(output, test.str());
//     test.str(std::string());
// }