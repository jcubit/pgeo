#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"

#include <numbers>
#include <cmath>

TEST(Determinant, TwoByTwo) {

    pgeo::Mat2f m = {{1.f, -5.f},
                     {2.f, -1.f}};
    // mut
    float det = pgeo::determinant(m);

    EXPECT_FLOAT_EQ(det, 9.f);
}

TEST(Determinant, TwoByTwoEqualRow) {

    pgeo::Mat2f m = {{1.f, 1.f},
                     {2.f, 2.f}};
    // mut
    float det = pgeo::determinant(m);

    EXPECT_FLOAT_EQ(det, 0.f);
}

TEST(Determinant, TwoByTwoDependentColumn) {

    pgeo::Mat2f m = {{2.f, 8.f},
                     {2.f, 8.f}};
    // mut
    float det = pgeo::determinant(m);

    EXPECT_FLOAT_EQ(det, 0.f);
}

TEST(Determinant, ThreebyThree) {

    pgeo::Mat3f m = {{2.f, 8.f, 1.f},
                     {2.f, 8.f, 1.f},
                     {2.f, 8.f, 1.f}};
    // mut
    float det = pgeo::determinant(m);

    EXPECT_FLOAT_EQ(det, 0.f);
}

TEST(Determinant, ThreeVectors) {

    constexpr float PI = std::numbers::pi;
    constexpr float theta = PI/4;
    float cosTheta = std::cos(theta);
    float sinTheta = std::sin(theta);

    pgeo::Vec3f v1 = {cosTheta, -sinTheta, 0.f};
    pgeo::Vec3f v2 = {sinTheta, cosTheta, 0.f};
    pgeo::Vec3f v3 = {0.f, 0.f, 1.f};
    // mut
    float det = pgeo::determinant(v1,v2,v3);

    EXPECT_FLOAT_EQ(det, 1.f);
}


//TEST(Determinant, FourByFour) {
//
//    float zNear = 0.01f;
//    float zFar = 1000;
//
//
//    pgeo::Mat4f m1 = {{1.f, 0.f,      0.f,                       0.f       },
//                      {0.f, 1.f,      0.f,                       0.f       },
//                      {0.f, 0.f,      0.f,                      -1.f       },
//                      {0.f, 0.f, 1.f / zFar - 1.f / zNear,      1.f / zNear}};
//
//    pgeo::Mat4f m1_inv = {{1.f, 0.f,      0.f,                       0.f       },
//                          {0.f, 1.f,      0.f,                       0.f       },
//                          {0.f, 0.f,  -zFar / (zFar -zNear),   -(zFar * zNear) / (zFar - zNear)},
//                          {0.f, 0.f,     -1.f,                      0.f}};
//
//
//    float sut = pgeo::determinant(m1);
//
//    EXPECT_EQ(sut, m1_inv);
//
//}