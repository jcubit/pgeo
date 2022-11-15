#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"

TEST(MatrixTest, Addition) {

    // list copy assignment
    pgeo::Mat2f m1 = {{1.0f, 2.0f},
                      {3.0f, 4.0f}};

    pgeo::Mat2f m2 = {{1.5f, -2.0f},
                      {-3.0f, 4.5f}};

    // sut
    pgeo::Mat2f m3 = m1 + m2;

    EXPECT_EQ(m3, pgeo::Mat2f({{2.5f, 0.0f},
                               {0.0f, 8.5f}}));
}

TEST(MatrixTest, VectorAddition) {

    // list copy assignment
    pgeo::Vec3f v1 = {1.0f, 2.0f, 3.0f};

    pgeo::Vec3f v2 = {-1.0f, 2.0f, -3.0f};

    // sut
    pgeo::Vec3f v3 = v1 + v2;

    EXPECT_EQ(v3, pgeo::Vec3f({0.0f, 4.0f, 0.0f}));
}

TEST(MatrixTest, CoVectorAddition) {

    // list copy assignment
    pgeo::CoVec3f v1 = {1.0f, 2.0f, 3.0f};

    pgeo::CoVec3f v2 = {-1.0f, 2.0f, -3.0f};

    // sut
    pgeo::CoVec3f v3 = v1 + v2;
    print(v1, "v1");
    print(v2, "v2");
    print(v3, "v3");

    EXPECT_EQ(v3, pgeo::CoVec3f({0.0f, 4.0f, 0.0f}));
}