#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"



TEST(Vector, Constructors) {

    // list copy assignment
    pgeo::Vec3f v1 = {1.0f, 2.0f, 3.0f};

    // sut
    EXPECT_EQ(v1(0), 1.0f);
    EXPECT_EQ(v1(1), 2.0f);
    EXPECT_EQ(v1(2), 3.0f);

    // list copy constructor
    pgeo::Vec3f v2({1.0f, 2.0f, 3.0f});

    // sut
    EXPECT_EQ(v2, v1);

    // copy constructor
    pgeo::Vec3f v3(v1);

    // sut
    EXPECT_EQ(v3, v1);

    // copy assignment
    pgeo::Vec3f v4 = v1;

    // sut
    EXPECT_EQ(v4, v1);

    pgeo::Vec3f v5({3.14f, 0.0f, 100.0f});
    pgeo::Vec3f v6 = v5;

    // move constructor
    pgeo::Vec3f v7(std::move(v5));

    // sut
    EXPECT_EQ(v7, v6);

    // move assignment
    pgeo::Vec3f v8({3.14f, 0.0f, 100.0f});
    pgeo::Vec3f v9 = v8;

    pgeo::Vec3f v10 = std::move(v8);

    // sut
    EXPECT_EQ(v10, v9);

}


TEST(Vector, ContainerConstructors) {

    // list copy assignment
    pgeo::Vec3f v1 = {1.0f, 2.0f, 3.0f};

    // std::array constructor
    std::array<float,3> array{1.0f, 2.0f, 3.0f};
    pgeo::Vec3f v2(array);

    // sut
    EXPECT_EQ(v2, v1);

    // std::vector constructor
    std::vector<float> vector{1.0f, 2.0f, 3.0f};
    pgeo::Vec3f v3(vector);

    // sut
    EXPECT_EQ(v3, v1);

}