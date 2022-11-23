#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"

TEST(MatrixTest, Inverse) {

    float zNear = 0.01f;
    float zFar = 1000;


    pgeo::Mat4f m1 = {{1.f, 0.f,      0.f,                       0.f       },
                      {0.f, 1.f,      0.f,                       0.f       },
                      {0.f, 0.f,      0.f,                      -1.f       },
                      {0.f, 0.f, 1.f / zFar - 1.f / zNear,      1.f / zNear}};

    pgeo::Mat4f m1_inv = {{1.f, 0.f,      0.f,                       0.f       },
                          {0.f, 1.f,      0.f,                       0.f       },
                          {0.f, 0.f,  -zFar / (zFar -zNear),   -(zFar * zNear) / (zFar - zNear)},
                          {0.f, 0.f,     -1.f,                      0.f}};


    pgeo::Mat4f sut = pgeo::inverse(m1);

    EXPECT_EQ(sut, m1_inv);

}