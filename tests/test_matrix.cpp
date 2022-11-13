#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"



TEST(MatrixTest, Constructors) {

    // list copy assignment
    pgeo::Mat2f m1 = {{1.0f, 2.0f},
                      {3.0f, 4.0f}};
    print(m1);

    // sut
    EXPECT_EQ(m1(0,0), 1);
    EXPECT_EQ(m1(0,1), 2);
    EXPECT_EQ(m1(1,0), 3);
    EXPECT_EQ(m1(1,1), 4);

    // list copy constructor
    pgeo::Mat2f m2({{1.0f, 2.0f}, {3.0f, 4.0f}});

    // sut
    EXPECT_EQ(m2, m1);

    // copy constructor
    pgeo::Mat2f m3(m1);

    // sut
    EXPECT_EQ(m3, m1);


    // copy assignment
    pgeo::Mat2f m4 = m1;

    // sut
    EXPECT_EQ(m4, m1);

    pgeo::Mat2f m5({{3.14f, 0.0f}, {0.0f, 100.0f}});
    pgeo::Mat2f m6 = m5;

    // move constructor
    pgeo::Mat2f m7(std::move(m5));

    // sut
    EXPECT_EQ(m7, m6);

    // move assignment
    pgeo::Mat2f m8({{3.14f, 0.0f}, {0.0f, 100.0f}});
    pgeo::Mat2f m9 = m8;

    pgeo::Mat2f m10 = std::move(m8);

    // sut
    EXPECT_EQ(m10, m9);


}


TEST(MatrixTest, MatrixByteSize)
{
    // sut
    EXPECT_EQ(sizeof(pgeo::Mat<float,2,2>), sizeof(float) * 4);
}