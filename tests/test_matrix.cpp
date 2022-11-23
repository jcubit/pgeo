#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"



TEST(Matrix, Constructors) {

    // list copy assignment
    pgeo::Mat2f m1 = {{1.0f, 2.0f},
                      {3.0f, 4.0f}};

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

TEST(Matrix, Span)
{
    pgeo::Mat<float,3,4> m34 = { {1.0f, 2.0f,  3.0f, 4.0f},
                                 {5.0f, 6.0f,  7.0f, 8.0f},
                                 {9.0f, 10.0f, 11.0f, 12.0f}};

    auto s = m34.span();

    // sut
    EXPECT_EQ(s.extent(0), 3);
    EXPECT_EQ(s.extent(1), 4);

    EXPECT_EQ(s.stride(0), 4);
    EXPECT_EQ(s.stride(1), 1);


    pgeo::Mat<float,3,4> m34_{};

    for (size_t i = 0; i < s.extent(0); ++i) {
        for (int j = 0; j < s.extent(1); ++j) {
            m34_(i,j) = s(i,j);
        }
    }

    // sut
    EXPECT_EQ(m34, m34_);
}


TEST(Matrix, MatrixByteSize)
{
    // sut
    EXPECT_EQ(sizeof(pgeo::Mat<float,2,2>), sizeof(float) * 4);
}