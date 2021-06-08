#include "gtest/gtest.h"
#include "Rotor.h"

TEST(Rotor, constructor_empty)
{
    Rotor r;

    EXPECT_EQ(r[0], Vector3D({5, 0, -5}));
    EXPECT_EQ(r[1], Vector3D({5, 0, 5}));
    EXPECT_EQ(r[2], Vector3D({2.5, 4.33, -5}));
    EXPECT_EQ(r[3], Vector3D({2.5, 4.33, 5}));
    EXPECT_EQ(r[4], Vector3D({-2.5, 4.33, -5}));
    EXPECT_EQ(r[5], Vector3D({-2.5, 4.33, 5}));
    EXPECT_EQ(r[6], Vector3D({-5, 0, -5}));
    EXPECT_EQ(r[7], Vector3D({-5, 0, 5}));
    EXPECT_EQ(r[8], Vector3D({-2.5, -4.33, -5}));
    EXPECT_EQ(r[9], Vector3D({-2.5, -4.33, 5}));
    EXPECT_EQ(r[10], Vector3D({2.5, -4.33, -5}));
    EXPECT_EQ(r[11], Vector3D({2.5, -4.33, 5}));
}

TEST(Rotor, double_constructor)
{
    Rotor r({0, 0, 0, 0, 0, 0});

    EXPECT_EQ(r[0], Vector3D({0, 0, 0}));
    EXPECT_EQ(r[1], Vector3D({0, 0, 0}));
    EXPECT_EQ(r[2], Vector3D({0, 0, 0}));
    EXPECT_EQ(r[3], Vector3D({0, 0, 0}));
    EXPECT_EQ(r[4], Vector3D({0, 0, 0}));
    EXPECT_EQ(r[5], Vector3D({0, 0, 0}));
    EXPECT_EQ(r[6], Vector3D({0, 0, 0}));
    EXPECT_EQ(r[7], Vector3D({0, 0, 0}));
    EXPECT_EQ(r[8], Vector3D({0, 0, 0}));
    EXPECT_EQ(r[9], Vector3D({0, 0, 0}));
    EXPECT_EQ(r[10], Vector3D({0, 0, 0}));
    EXPECT_EQ(r[11], Vector3D({0, 0, 0}));

    Rotor r2({10, 10, 10, 5, 5, 5});

    EXPECT_EQ(r2[0], Vector3D({10, 10, 10}));
    EXPECT_EQ(r2[1], Vector3D({10, 10, 5}));
    EXPECT_EQ(r2[2], Vector3D({5, 5, 10}));
    EXPECT_EQ(r2[3], Vector3D({5, 5, 5}));
    EXPECT_EQ(r2[4], Vector3D({-5, 5, 10}));
    EXPECT_EQ(r2[5], Vector3D({-5, 5, 5}));
    EXPECT_EQ(r2[6], Vector3D({-10, 10, 10}));
    EXPECT_EQ(r2[7], Vector3D({-10, 10, 5}));
    EXPECT_EQ(r2[8], Vector3D({-5, -5, 10}));
    EXPECT_EQ(r2[9], Vector3D({-5, -5, 5}));
    EXPECT_EQ(r2[10], Vector3D({5, -5, 10}));
    EXPECT_EQ(r2[11], Vector3D({5, -5, 5}));
}

TEST(Rotor, Rotation)
{
    Rotor r;

    Matrix3x3 rot({1, 0, 0,
                   0, 1, 0,
                   0, 0, 1});

    EXPECT_EQ(r, Rotor());

    r.Rotation(rot);

    EXPECT_EQ(r, Rotor());

    set_Rotation_OZ(rot, 4);

    for (int i = 0; i < 90; i++)
    {
        r.Rotation(rot);
    }

    EXPECT_EQ(r, Rotor());

    set_Rotation_OZ(rot, -4);

    for (int i = 0; i < 90; i++)
    {
        r.Rotation(rot);
    }

    EXPECT_EQ(r, Rotor());

    set_Rotation_OZ(rot, -4);

    for (int i = 0; i < 36000; i++)
    {
        r.Rotation(rot);
    }

    EXPECT_EQ(r, Rotor());
}

TEST(Rotor, Translation)
{
    Rotor r;

    r.Translate(Vector3D());

    EXPECT_EQ(r, Rotor());

    r.Translate(Vector3D({10, 50, 123.33}));

    r.Translate(Vector3D({0.55, 9, -1}));

    r.Translate(Vector3D({-10.55, -59, -122.33}));

    EXPECT_EQ(r, Rotor());
}