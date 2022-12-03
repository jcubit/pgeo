#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"

TEST(InnerProduct, TwoByTwoMatrices) {

    pgeo::Mat2f m1 = {{1.0f, 2.0f},
                      {3.0f, 4.0f}};

    pgeo::Mat2f m2 = {{0.5f, -2.0f},
                      {-3.0f, 4.0f}};

    // MUT
    float scalar = pgeo::innerProduct(m1, m2);

    EXPECT_FLOAT_EQ(scalar, 3.5f);
}

