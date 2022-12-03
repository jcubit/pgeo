#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"


TEST(meet, FromThreePlanes) {

    pgeo::Plane3f a1 = {0,-1,0,1};
    pgeo::Plane3f a2 = {1,0,0,0};
    pgeo::Plane3f a3 = {0,0,1,0};

    // MUT
    pgeo::Point3f p = pgeo::meet(a1,a2,a3);

    EXPECT_EQ(p, pgeo::Point3f({0,1,0,1}));
}

TEST(join, EvenPermutationKeepsOrientation) {

    pgeo::Point3f p0 = { -0.5f, -0.5f, -0.5f, 1.f};
    pgeo::Point3f p4 = { -0.5f, -0.5f,  0.5f, 1.f};
    pgeo::Point3f p6 = { -0.5f,  0.5f,  0.5f, 1.f};

    // MUT
    pgeo::Plane3f a = pgeo::join(p0,p4,p6);
    pgeo::Vec3f n = a.w() > 0 ? a.xyz() : -1 * a.xyz();

    pgeo::Vec3f v = {1,0,0};
    EXPECT_EQ(n, v);

    // MUT
    pgeo::Plane3f b = pgeo::join(p4,p6,p0);
    pgeo::Vec3f m = b.w() > 0 ? b.xyz() : -1 * b.xyz();
    EXPECT_EQ(n, m);

    // MUT
    pgeo::Plane3f c = pgeo::join(p6,p0,p4);
    pgeo::Vec3f n_c = c.w() > 0 ? c.xyz() : -1 * c.xyz();
    EXPECT_EQ(n, n_c);

    // MUT
    pgeo::Plane3f d = pgeo::join(p0, p6,p4);
    pgeo::Vec3f n_d = d.w() > 0 ? d.xyz() : -1 * d.xyz();
    n_d = -1 * n_d;
    EXPECT_EQ(a.xyz(), n_d);
}

TEST(join, OddPermutationFlipsOrientation) {

    pgeo::Point3f p0 = { -0.5f, -0.5f, -0.5f, 1.f};
    pgeo::Point3f p4 = { -0.5f, -0.5f,  0.5f, 1.f};
    pgeo::Point3f p6 = { -0.5f,  0.5f,  0.5f, 1.f};


    pgeo::Plane3f a = pgeo::join(p0,p4,p6);
    pgeo::Vec3f n = a.w() > 0 ? a.xyz() : -1 * a.xyz();

    // MUT
    pgeo::Plane3f d = pgeo::join(p0, p6,p4);
    pgeo::Vec3f n_d = d.w() > 0 ? d.xyz() : -1 * d.xyz();
    n_d = -1 * n_d;
    EXPECT_EQ(a.xyz(), n_d);
}

TEST(join, JoinFace1FromPoints) {

    pgeo::Point3f p0 = {0.5f,-0.5f,-0.5f,1.f};
    pgeo::Point3f p4 = {0.5f, 0.5f,-0.5f,1.f};
    pgeo::Point3f p6 = {0.5f,-0.5f, 0.5f,1.f};
    pgeo::Point3f p2 = {0.5f, 0.5f, 0.5f,1.f};

    // MUT
    pgeo::Plane3f a = pgeo::join(p0,p4,p6);
    pgeo::Plane3f b = pgeo::join(p0,p6,p2);

    EXPECT_EQ(a, b);
}

TEST(join, JoinFace2FromPoints) {

    pgeo::Point3f p1 = {0.5f,-0.5f,-0.5f,1.f};
    pgeo::Point3f p3 = {0.5f, 0.5f,-0.5f,1.f};
    pgeo::Point3f p5 = {0.5f,-0.5f, 0.5f,1.f};
    pgeo::Point3f p7 = {0.5f, 0.5f, 0.5f,1.f};

    // MUT
    pgeo::Plane3f a = pgeo::join(p1,p3,p5);
    pgeo::Plane3f b = pgeo::join(p7,p3,p5);


    EXPECT_EQ(a, b);
}

