#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"


TEST(Point, InitListConstructor) {

    // list copy constructor
    pgeo::Point3f p({1,2,3,1});

    // sut
    EXPECT_EQ(p(0), 1);
    EXPECT_EQ(p(1), 2);
    EXPECT_EQ(p(2), 3);
}


TEST(Point, InitListCopyAssignment) {

    // list copy assignment
    pgeo::Point3f p1 = {1.0f, 2.0f, 3.0f, 1.f};

    // sut
    EXPECT_EQ(p1(0), 1);
    EXPECT_EQ(p1(1), 2);
    EXPECT_EQ(p1(2), 3);
}

TEST(Point, CopyConstructorAndCopyAssignment) {

    // list copy assignment
    pgeo::Point3f p1 = {1.0f, 2.0f, 3.0f, 1.f};

    // mut: copy constructor
    pgeo::Point3f p3(p1);

    EXPECT_EQ(p3, p1);

    // copy assignment
    pgeo::Point3f p4 = p1;

    // sut
    EXPECT_EQ(p4, p1);
}

TEST(Point, MoveConstructorAndAssignment) {


    pgeo::Point3f p5({3.14f, 0.0f, 2.74f, 1.f});
    pgeo::Point3f p6 = p5;

    // move constructor
    pgeo::Point3f p7(std::move(p5));

    // sut
    EXPECT_EQ(p7, p6);

    // move assignment
    pgeo::Point3f p8({{3.14f, 0.0f, 100.0f, 1.f}});
    pgeo::Point3f p9 = p8;

    pgeo::Point3f p10 = std::move(p8);

    // sut
    EXPECT_EQ(p10, p9);

}

TEST(Point, 4DVectorConstructor)
{
    pgeo::Vec4f v = {1.f,2.f,3.f,1.0f};
    pgeo::Point3f p(v);
    pgeo::Point3f q({1.f,2.f,3.f,1.f});

    // sut
    EXPECT_EQ(p, q);

}

TEST(Point, 4DConstructor)
{
    pgeo::Point3f p(1.f,2.f,3.f,4.f);
    pgeo::Point3f q({1.f,2.f,3.f,4.f});

    // sut
    EXPECT_EQ(p, q);

}

TEST(Point, ElementAccess)
{
    pgeo::Point3f p(1.f,2.f,3.f,4.f);

    // mut
    EXPECT_FLOAT_EQ(p(0), 1.f);
    EXPECT_FLOAT_EQ(p(1), 2.f);
    EXPECT_FLOAT_EQ(p(2), 3.f);
    EXPECT_FLOAT_EQ(p(3), 4.f);

}



