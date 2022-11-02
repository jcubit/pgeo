#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"

TEST(MatrixTest, Addition) {

    // list copy assignment
    pgeo::Mat22f m1 = {{1.0f, 2.0f},
                       {3.0f, 4.0f}};

    pgeo::Mat22f m2 = {{1.5f, -2.0f},
                       {-3.0f, 4.5f}};

    print(m1);
    print(m2);

    // sut
    pgeo::Mat22f m3 = m1 + m2;

    print(m3);

    pgeo::Mat22f m = {{2.5f, 0.0f},
                      {0.0f, 8.5f}};

    EXPECT_EQ(m3, m);



}