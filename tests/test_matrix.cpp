#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"

TEST(MatrixTest, Constructors) {

    // list copy assignment
    pgeo::Mat22f m1 = {{1.0f, 2.0f},
                       {3.0f, 4.0f}};
    print(m1);

    // sut
    EXPECT_EQ(m1(0,0), 1);
    EXPECT_EQ(m1(0,1), 2);
    EXPECT_EQ(m1(1,0), 3);
    EXPECT_EQ(m1(1,1), 4);

    // list copy constructor
    pgeo::Mat22f m2({{1.0f, 2.0f}, {3.0f, 4.0f}});

    // sut
    EXPECT_EQ(m2, m1);

    // copy constructor
    pgeo::Mat22f m3(m1);

    // sut
    EXPECT_EQ(m3, m1);


    // copy assignment
    pgeo::Mat22f m4 = m1;

    // sut
    EXPECT_EQ(m4, m1);


}