#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"

TEST(Point, CopyConstructor) {

    // list copy assignment
    pgeo::Point3f p1 = {1.0f, 2.0f, 3.0f};

    // sut
    EXPECT_EQ(p1(0), 1);
    EXPECT_EQ(p1(1), 2);
    EXPECT_EQ(p1(2), 3);

}

TEST(Point, Constructors) {

    // list copy assignment
    pgeo::Point3f p1 = {1.0f, 2.0f, 3.0f};

    // sut
    EXPECT_EQ(p1(0), 1);
    EXPECT_EQ(p1(1), 2);
    EXPECT_EQ(p1(2), 3);

    // list copy constructor
    pgeo::Point3f p2({1,2,3});

    // sut
    EXPECT_EQ(p2, p1);

    // copy constructor
    pgeo::Point3f p3(p1);

    // sut
    EXPECT_EQ(p3, p1);


    // copy assignment
    pgeo::Point3f p4 = p1;

    // sut
    EXPECT_EQ(p4, p1);

    pgeo::Point3f p5({3.14f, 0.0f, 2.74f});
    pgeo::Point3f p6 = p5;

    // move constructor
    pgeo::Point3f p7(std::move(p5));

    // sut
    EXPECT_EQ(p7, p6);

    // move assignment
    pgeo::Point3f p8({{3.14f, 0.0f, 100.0f}});
    pgeo::Point3f p9 = p8;

    pgeo::Point3f p10 = std::move(p8);

    // sut
    EXPECT_EQ(p10, p9);

}

TEST(Point, Meet) {

    pgeo::Plane3f a1 = {0,-1,0,1};
    pgeo::Plane3f a2 = {1,0,0,0};
    pgeo::Plane3f a3 = {0,0,1,0};
    print(a1);

    // mut
    pgeo::Point3f p = pgeo::meet(a1,a2,a3);
    print(p, "p");


    EXPECT_EQ(p, pgeo::Point3f({0,1,0,1}));

}