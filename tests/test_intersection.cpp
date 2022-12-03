#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"
#include "common.h"

TEST(meet, IntersectPlane) {

    pgeo::Point3f p0 = {-0.5, -0.5, -0.5, 1.};
    pgeo::Point3f p2 = { 0.5, -0.5, -0.5, 1.};
    pgeo::Point3f p3 = {-0.5,  0.5, -0.5, 1.};

    pgeo::Plane3f a = pgeo::join(p0,p2,p3);

    pgeo::Line3f line(pgeo::Point3f(0.f, 0.f, -2.f, 1.f),
                      pgeo::Point3f(0.f, 0.f, 2.f, 1.f));

    // MUT
    pgeo::Point3f p = pgeo::meet(line, a);
    EXPECT_EQ(p, pgeo::Point3f({0.f, 0.f, -0.5f, 1.f}));
}

TEST(meet, IntersectSamePlaneDifferentRep) {

    pgeo::Point3f p0 = {-0.5, -0.5, -0.5, 1.};
    pgeo::Point3f p2 = { 0.5, -0.5, -0.5, 1.};
    pgeo::Point3f p3 = {-0.5,  0.5, -0.5, 1.};
    pgeo::Point3f p1 = { 0.5,  0.5, -0.5, 1.};

    pgeo::Plane3f a = pgeo::join(p0,p2,p3);
    pgeo::Plane3f b = pgeo::join(p0,p3,p1);

    pgeo::Line3f line(pgeo::Point3f(0.f, 0.f, -2.f, 1.f),
                      pgeo::Point3f(0.f, 0.f, 2.f, 1.f));

    // MUT
    pgeo::Point3f p = pgeo::meet(line, a);
    pgeo::Point3f q = pgeo::meet(line, b);

    EXPECT_EQ(p, q);
}

TEST(meet, IntersectAtInfinity) {

    pgeo::Point3f p0 = {-0.5, -0.5, -0.5, 1.};
    pgeo::Point3f p2 = { 0.5, -0.5, -0.5, 1.};
    pgeo::Point3f p3 = {-0.5,  0.5, -0.5, 1.};

    pgeo::Plane3f a = pgeo::join(p0,p2,p3);

    pgeo::Line3f line(pgeo::Point3f(-0.5f, -0.5f, -2.f, 1.f),
                      pgeo::Point3f(0.5f, -0.5f, -2.f, 1.f));

    // MUT
    pgeo::Point3f p = pgeo::meet(line, a);
    EXPECT_FLOAT_EQ(p.w(), 0);
}

TEST(join, LineAndNonCollinearPoint) {

    pgeo::Point3f p0 = {-0.5, -0.5, -0.5, 1.};
    pgeo::Point3f p2 = { 0.5, -0.5, -0.5, 1.};
    pgeo::Point3f p3 = {-0.5,  0.5, -0.5, 1.};

    pgeo::Plane3f a = pgeo::join(p0,p2,p3);
    pgeo::Line3f line(p0,p2);

    // MUT
    pgeo::Plane3f b = pgeo::join(line, p3);
    EXPECT_EQ(a, b);
}

TEST(join, LineAndCollinearPoint) {

    pgeo::Point3f p0 = {-0.5, -0.5, -0.5, 1.};
    pgeo::Point3f p2 = { 0.5, -0.5, -0.5, 1.};
    pgeo::Point3f p3 = {-0.5,  0.5, -0.5, 1.};

    pgeo::Line3f line(p0,p2);

    // MUT
    pgeo::Plane3f a = pgeo::join(line, p2);
    EXPECT_EQ(a.w(), 0);
}