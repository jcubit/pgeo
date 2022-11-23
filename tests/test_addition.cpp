#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"

TEST(MatrixTest, Addition) {

    pgeo::Mat2f m1 = {{1.0f, 2.0f},
                      {3.0f, 4.0f}};

    pgeo::Mat2f m2 = {{1.5f, -2.0f},
                      {-3.0f, 4.5f}};

    // sut
    pgeo::Mat2f m3 = m1 + m2;

    EXPECT_EQ(m3, pgeo::Mat2f({{2.5f, 0.0f},
                               {0.0f, 8.5f}}));
}

TEST(Vector, Addition) {

    pgeo::Vec3f v1 = {1.0f, 2.0f, 3.0f};

    pgeo::Vec3f v2 = {-1.0f, 2.0f, -3.0f};

    // sut
    pgeo::Vec3f v3 = v1 + v2;

    EXPECT_EQ(v3, pgeo::Vec3f({0.0f, 4.0f, 0.0f}));
}

TEST(CoVector, Addition) {

    pgeo::CoVec3f v1 = {1.0f, 2.0f, 3.0f};

    pgeo::CoVec3f v2 = {-1.0f, 2.0f, -3.0f};

    // sut
    pgeo::CoVec3f v3 = v1 + v2;
    print(v1, "v1");
    print(v2, "v2");
    print(v3, "v3");

    EXPECT_EQ(v3, pgeo::CoVec3f({0.0f, 4.0f, 0.0f}));
}

TEST(Vector, AdditionWithView) {

    pgeo::Mat<float, 3, 2> m = {{-1.0f, -2.0f},
                                {3.0f, 4.0f},
                                {-3.0f, 4.0f}};

    pgeo::Vec3f t = m.submatrix(0,3,0,1);

    pgeo::Vec3f v = {1.0f, 2.0f, 3.0f};

    // sut
    pgeo::Vec3f result = v + pgeo::Vec3f(m.submatrix(0,3,0,1)) + t;

    EXPECT_EQ(result, pgeo::Vec3f({-1.0f, 8.0f, -3.0f}));
}