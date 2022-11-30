#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"


TEST(Point, Meet) {

    pgeo::Plane3f a1 = {0,-1,0,1};
    pgeo::Plane3f a2 = {1,0,0,0};
    pgeo::Plane3f a3 = {0,0,1,0};

    // mut
    pgeo::Point3f p = pgeo::meet(a1,a2,a3);

    EXPECT_EQ(p, pgeo::Point3f({0,1,0,1}));
}

TEST(Point, Join) {

    pgeo::Point3f p1 = {0.5f,-0.5f,-0.5f,1.f};
    pgeo::Point3f p3 = {0.5f, 0.5f,-0.5f,1.f};
    pgeo::Point3f p5 = {0.5f,-0.5f, 0.5f,1.f};
    pgeo::Point3f p7 = {0.5f, 0.5f, 0.5f,1.f};

    // mut
    pgeo::Plane3f a = pgeo::join(p1,p3,p5);
    pgeo::Plane3f b = pgeo::join(p7,p3,p5);
    print(a, "a");
    print(b, "b");

    EXPECT_EQ(a, b);
}