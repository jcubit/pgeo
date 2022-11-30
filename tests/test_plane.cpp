#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"


TEST(Plane, InitListConstructor) {

    // list copy constructor
    pgeo::Plane3f p({1,2,3,1});

    // sut
    EXPECT_EQ(p(0), 1);
    EXPECT_EQ(p(1), 2);
    EXPECT_EQ(p(2), 3);
}


TEST(Plane, InitListCopyAssignment) {

    // list copy assignment
    pgeo::Plane3f p1 = {1.0f, 2.0f, 3.0f, 1.f};

    // sut
    EXPECT_EQ(p1(0), 1);
    EXPECT_EQ(p1(1), 2);
    EXPECT_EQ(p1(2), 3);
}

TEST(Plane, CopyConstructorAndCopyAssignment) {

    // list copy assignment
    pgeo::Plane3f p1 = {1.0f, 2.0f, 3.0f, 1.f};

    // mut: copy constructor
    pgeo::Plane3f p3(p1);

    EXPECT_EQ(p3, p1);

    // copy assignment
    pgeo::Plane3f p4 = p1;

    // sut
    EXPECT_EQ(p4, p1);
}

TEST(Plane, MoveConstructorAndAssignment) {


    pgeo::Plane3f p5({3.14f, 0.0f, 2.74f, 1.f});
    pgeo::Plane3f p6 = p5;

    // move constructor
    pgeo::Plane3f p7(std::move(p5));

    // sut
    EXPECT_EQ(p7, p6);

    // move assignment
    pgeo::Plane3f p8({{3.14f, 0.0f, 100.0f, 1.f}});
    pgeo::Plane3f p9 = p8;

    pgeo::Plane3f p10 = std::move(p8);

    // sut
    EXPECT_EQ(p10, p9);

}

TEST(Plane, FourDCoVectorConstructor)
{
    pgeo::CoVec4f v = {1.f,2.f,3.f,1.0f};
    pgeo::Plane3f p(v);
    pgeo::Plane3f q({1.f,2.f,3.f,1.f});

    // sut
    EXPECT_EQ(p, q);

}

TEST(Plane, FourDConstructor)
{
    pgeo::Plane3f p(1.f,2.f,3.f,4.f);
    print(p,"p");
    pgeo::Plane3f q({1.f,2.f,3.f,4.f});

    // sut
    EXPECT_EQ(p, q);
}



