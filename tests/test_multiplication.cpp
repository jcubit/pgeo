#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"

TEST(MatrixTest, Multiplication) {

    pgeo::Mat2f m1 = {{1.0f, 2.0f},
                      {3.0f, 4.0f}};

    pgeo::Mat2f m2 = {{1.5f, -2.0f},
                      {-3.0f, 4.5f}};

    // sut
    pgeo::Mat2f m3 = m1 * m2;


    EXPECT_EQ(m3, pgeo::Mat2f({{-4.5f, 7.0f},
                               {-7.5f, 12.0f}}));
}