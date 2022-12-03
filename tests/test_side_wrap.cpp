#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"
#include "common.h"

TEST(SideWrap, Coplanar) {

    Cube<float> cube{};

    pgeo::Line3f l1(cube(0),cube(1));
    pgeo::Line3f l2(cube(0),cube(2));

    // MUT
    float sideWrap = pgeo::sideWrap(l1,l2);

    EXPECT_FLOAT_EQ(sideWrap, 0);
}

TEST(SideWrap, Parallel) {

    Cube<float> cube{};

    pgeo::Line3f l1(cube(0),cube(1));
    pgeo::Line3f l2(cube(3),cube(2));

    // MUT
    float sideWrap = pgeo::sideWrap(l1,l2);

    EXPECT_FLOAT_EQ(sideWrap, 0);
}

TEST(SideWrap, HitCube) {

    Cube<float> cube{};

    pgeo::Line3f line(pgeo::Point3f(0.f, 0.f, -2.f, 1.f),
                      pgeo::Point3f(0.f, 0.f, 2.f, 1.f));

    float e0 = sideWrap(line, pgeo::Line3f(cube(7),cube(5)));
    float e1 = sideWrap(line, pgeo::Line3f(cube(5),cube(1)));
    float e2 = sideWrap(line, pgeo::Line3f(cube(1), cube(3)));
    float e3 = sideWrap(line, pgeo::Line3f(cube(3), cube(7)));
    float e4 = sideWrap(line, pgeo::Line3f(cube(4), cube(6)));
    float e5 = sideWrap(line, pgeo::Line3f(cube(6), cube(2)));
    float e6 = sideWrap(line, pgeo::Line3f(cube(2), cube(0)));
    float e7 = sideWrap(line, pgeo::Line3f(cube(0), cube(4)));
    float e8 = sideWrap(line, pgeo::Line3f(cube(6), cube(7)));
    float e9 = sideWrap(line, pgeo::Line3f(cube(3), cube(2)));
    float e10 = sideWrap(line, pgeo::Line3f(cube(5), cube(4)));
    float e11 = sideWrap(line, pgeo::Line3f(cube(0), cube(1)));

    EXPECT_TRUE(e0 < 0);
    EXPECT_TRUE(e1 == 0);
    EXPECT_TRUE(e2 > 0);
    EXPECT_TRUE(e3 == 0);
    EXPECT_TRUE(e4 < 0);
    EXPECT_TRUE(e5 == 0);
    EXPECT_TRUE(e6 > 0);
    EXPECT_TRUE(e7 == 0);
    EXPECT_TRUE(e8 < 0);
    EXPECT_TRUE(e9 > 0);
    EXPECT_TRUE(e10 < 0);
    EXPECT_TRUE(e11 > 0);
}
