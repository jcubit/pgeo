#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"

TEST(Matrix, Multiplication) {

    pgeo::Mat2f m1 = {{1.0f, 2.0f},
                      {3.0f, 4.0f}};

    pgeo::Mat2f m2 = {{1.5f, -2.0f},
                      {-3.0f, 4.5f}};

    // mut
    pgeo::Mat2f m3 = m1 * m2;


    EXPECT_EQ(m3, pgeo::Mat2f({{-4.5f, 7.0f},
                               {-7.5f, 12.0f}}));
}

TEST(Matrix, LeftScalarMultiplication) {

    pgeo::Mat2f m1 = {{1.0f, 2.0f},
                      {3.0f, 4.0f}};
    // mut
    pgeo::Mat2f m3 = 2.0 * m1;

    EXPECT_EQ(m3, pgeo::Mat2f({{2.f, 4.0f},
                               {6.f, 8.0f}}));
}

TEST(Matrix, RightScalarMultiplication) {

    pgeo::Mat2f m1 = {{1.0f, 2.0f},
                      {3.0f, 4.0f}};
    // mut
    pgeo::Mat2f m3 = m1 * 2.0;

    EXPECT_EQ(m3, pgeo::Mat2f({{2.f, 4.0f},
                               {6.f, 8.0f}}));
}

TEST(Matrix, linearCombination) {

    pgeo::Mat2f m1 = {{1.0f, 2.0f},
                      {3.0f, 4.0f}};

    pgeo::Mat2f m2 = {{1.5f, -2.0f},
                      {-3.0f, 4.5f}};
    // mut
    pgeo::Mat2f m3 = 2.0 * m1 + 0.5 * m2;

    EXPECT_EQ(m3, pgeo::Mat2f({{2.75f, 3.0f},
                               {4.5f, 10.25f}}));
}

TEST(Matrix, MatrixVectorMultiplication) {

    pgeo::Mat2f m = {{1.0f, 2.0f},
                      {3.0f, 4.0f}};

    pgeo::Vec2f v = {1.0f, -2.0f};

    // MUT
    pgeo::Vec2f result = m*v;
    print(result);

    EXPECT_EQ(result, pgeo::Vec2f({-3.f, -5.f}));


}