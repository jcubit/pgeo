#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"


TEST(Line, PointConstructor) {

    pgeo::Point3f p = {0,0,0,1};
    pgeo::Point3f q = {1,0,0,1};

    // mut
    pgeo::Line3f line(p,q);

    EXPECT_EQ(line.p, p);
    EXPECT_EQ(line.q, q);
}

TEST(Line, Covariant) {

    pgeo::Point3f p1 = {0,0,0,1};
    pgeo::Point3f p2 = {1,0,0,1};

    pgeo::Line3f line(p1,p2);

    // mut
    pgeo::Mat4f L = line.covariant();

    pgeo::Mat4f m = {{ 0.000, 0.000, 0.000,-1.000 },
                     { 0.000, 0.000, 0.000, 0.000 },
                     { 0.000, 0.000, 0.000, 0.000 },
                     { 1.000, 0.000, 0.000, 0.000 }};

    EXPECT_EQ(L, m);
}

TEST(Line, ReverseDirection)
{
    pgeo::Point3f p = {0,0,0,1};
    pgeo::Point3f q = {1,0,0,1};
    pgeo::Line3f line(p,q);

    line.reverseDirection();

    EXPECT_EQ(line.p, q);
    EXPECT_EQ(line.q, p);
}