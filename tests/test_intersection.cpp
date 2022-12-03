#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"
#include "common.h"

TEST(meet, IntersectSamePlaneDifferentRep) {

    pgeo::Point3f p0 = {-0.5, -0.5, -0.5, 1.};
    pgeo::Point3f p2 = { 0.5, -0.5, -0.5, 1.};
    pgeo::Point3f p3 = {-0.5,  0.5, -0.5, 1.};
    pgeo::Point3f p1 = { 0.5,  0.5, -0.5, 1.};

    pgeo::Plane3f a = pgeo::join(p0,p2,p3);
    pgeo::Plane3f b = pgeo::join(p0,p3,p1);

    EXPECT_EQ(a, b);

    pgeo::Line3f line(pgeo::Point3f(0.f, 0.f, -2.f, 1.f),
                      pgeo::Point3f(0.f, 0.f, 2.f, 1.f));

    pgeo::Point3f p = pgeo::meet(line, a);

    print(p,"p");

}