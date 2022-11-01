#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"
// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(MatrixTest, Constructors) {

    // list copy assignment
    pgeo::Mat22f m1 = {{1.0f, 2.0f},
                       {3.0f, 4.0f}};
    print(m1);

    // sut
    EXPECT_EQ(m1(0,0), 1);
    EXPECT_EQ(m1(0,1), 2);
    EXPECT_EQ(m1(1,0), 3);
    EXPECT_EQ(m1(1,1), 4);

    // list copy constructor
    pgeo::Mat22f m2({{1.0f, 2.0f}, {3.0f, 4.0f}});

    // sut
    EXPECT_EQ(m2(0,0), 1);
    EXPECT_EQ(m2(0,1), 2);
    EXPECT_EQ(m2(1,0), 3);
    EXPECT_EQ(m2(1,1), 4);

    // copy constructor
    pgeo::Mat22f m3(m1);

    // sut
    EXPECT_EQ(m3(0,0), m1(0,0));
    EXPECT_EQ(m3(0,1), m1(0,1));
    EXPECT_EQ(m3(1,0), m1(1,0));
    EXPECT_EQ(m3(1,1), m1(1,1));

    // copy assignment
    pgeo::Mat22f m4 = m1;

    // sut
    EXPECT_EQ(m4(0,0), m1(0,0));
    EXPECT_EQ(m4(0,1), m1(0,1));
    EXPECT_EQ(m4(1,0), m1(1,0));
    EXPECT_EQ(m4(1,1), m1(1,1));




}

