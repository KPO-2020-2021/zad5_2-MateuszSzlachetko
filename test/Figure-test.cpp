#include "gtest/gtest.h"
#include "Figure.h"

TEST(Figure, string_constructor)
{
    Figure test("test");

    EXPECT_EQ(test.Get_name(), "test");

    Figure test1("tsdadsd123123123qqawsdasdasdqaww123ikoj123u1980udkasmnkodjq9i21ut");

    EXPECT_EQ(test1.Get_name(), "tsdadsd123123123qqawsdasdasdqaww123ikoj123u1980udkasmnkodjq9i21ut");

    Figure test2("Rotor");

    EXPECT_EQ(test2.Get_name(), "Rotor");
}

TEST(Figure, append_name)
{
    Figure test("test");

    EXPECT_EQ(test.Get_name(), "test");

    test.Update_name("tset");

    EXPECT_EQ(test.Get_name(), "testtset");

    test.Update_name("   test");

    EXPECT_EQ(test.Get_name(), "testtset   test");

    test.Update_name(".txt");

    EXPECT_EQ(test.Get_name(), "testtset   test.txt");
}