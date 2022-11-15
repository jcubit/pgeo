#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"


TEST(Submatrix, copySubmatrix)
{
    pgeo::Mat4f m1 = {{1.0f, 2.0f, 3.0f, 1.0f},
                      {1.0f, 2.0f, 3.0f, 1.0f},
                      {1.0f, 2.0f, 3.0f, 1.0f},
                      {1.0f, 2.0f, 3.0f, 1.0f}};

    pgeo::Mat3f m2 = m1.submatrix(0, 3, 0, 3);
    print(m2);

    pgeo::Mat3f m = {{1.0f, 2.0f, 3.0f},
                      {1.0f, 2.0f, 3.0f},
                      {1.0f, 2.0f, 3.0f}};

    EXPECT_EQ(m2, m);

}

TEST(Submatrix, changeSubmatrix)
{
    pgeo::Mat4f m1 = {{1.0f, 2.0f, 3.0f, 1.0f},
                      {1.0f, 2.0f, 3.0f, 1.0f},
                      {1.0f, 2.0f, 3.0f, 1.0f},
                      {1.0f, 2.0f, 3.0f, 1.0f}};


    m1.submatrix(0, 3, 0, 3) = {{1.0f, 2.0f, 3.0f},
                                {4.0f, 5.0f, 6.0f},
                                {7.0f, 8.0f, 9.0f}};

    pgeo::Mat4f m = {{1.0f, 2.0f, 3.0f, 1.0f},
                      {4.0f, 5.0f, 6.0f, 1.0f},
                      {7.0f, 8.0f, 9.0f, 1.0f},
                      {1.0f, 2.0f, 3.0f, 1.0f}};

    EXPECT_EQ(m, m1);

}


TEST(MatrixTranspose, Size)
{
    pgeo::Mat<float,3,2> m32 = { {1.0f,2.0f},
                                 {3.0f,4.0f},
                                 {5.0f,6.0f}};

    print(m32, "m32 =");

    // sut
    EXPECT_EQ(m32.columns(), 2);
    EXPECT_EQ(m32.rows(), 3);

    pgeo::Mat<float,2,3> m23 = m32.t();
    print(m23);
    // sut
    EXPECT_EQ(m23.columns(), 3);
    EXPECT_EQ(m23.rows(), 2);
}

TEST(MatrixTranspose, copyTranspose)
{
    pgeo::Mat<float,3,2> m32 = { {1.0f,2.0f},
                                 {3.0f,4.0f},
                                 {5.0f,6.0f}};
    pgeo::Mat<float,2,3> m23 = m32.t();

    pgeo::Mat<float,2,3> m = {{1.000, 3.000, 5.000},
                              {2.000, 4.000, 6.000}};

    // sut
    EXPECT_EQ(m23, m);

}



