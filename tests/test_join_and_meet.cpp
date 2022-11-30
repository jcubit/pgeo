#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"


TEST(Point, Meet) {

    pgeo::Plane3f a1 = {0,-1,0,1};
    pgeo::Plane3f a2 = {1,0,0,0};
    pgeo::Plane3f a3 = {0,0,1,0};

    // mut
    pgeo::Point3f p = pgeo::meet(a1,a2,a3);

    EXPECT_EQ(p, pgeo::Point3f({0,1,0,1}));
}

TEST(Point, JoinOrientation) {

    pgeo::Point3f p0 = { -0.5f, -0.5f, -0.5f, 1.f};
    pgeo::Point3f p4 = { -0.5f, -0.5f,  0.5f, 1.f};
    pgeo::Point3f p6 = { -0.5f,  0.5f,  0.5f, 1.f};


    // mut
    pgeo::Plane3f a = pgeo::join(p0,p4,p6);
    pgeo::Vec3f n = a.xyz();
    print(a, "a");
    print(n, "n");

    pgeo::Vec3f v = {1,0,0};
    EXPECT_EQ(n, v);

    // mut
    pgeo::Plane3f b = pgeo::join(p4,p6,p0);
    pgeo::Vec3f m = b.xyz();
    EXPECT_EQ(n, m);

    print(b, "b");
    print(m, "m");

    // mut
    pgeo::Plane3f c = pgeo::join(p6,p0,p4);
    pgeo::Vec3f n_c = c.xyz();
    EXPECT_EQ(n, n_c);

    print(n_c, "n_c");
    print(c, "c");

    // mut
    pgeo::Plane3f d = pgeo::join(p0, p6,p4);
    pgeo::Vec3f n_d = d.xyz();
    EXPECT_EQ(n, -1 * n_d);

    print(d, "d");
    print(n_d, "n_d");


}

TEST(Point, JoinFace1) {

    pgeo::Point3f p0 = {0.5f,-0.5f,-0.5f,1.f};
    pgeo::Point3f p4 = {0.5f, 0.5f,-0.5f,1.f};
    pgeo::Point3f p6 = {0.5f,-0.5f, 0.5f,1.f};
    pgeo::Point3f p2 = {0.5f, 0.5f, 0.5f,1.f};

    // mut
    pgeo::Plane3f a = pgeo::join(p0,p4,p6);
    pgeo::Plane3f b = pgeo::join(p0,p6,p2);
    print(a, "a");
    print(b, "b");

    EXPECT_EQ(a, b);
}

TEST(Point, JoinFace2) {

    pgeo::Point3f p1 = {0.5f,-0.5f,-0.5f,1.f};
    pgeo::Point3f p3 = {0.5f, 0.5f,-0.5f,1.f};
    pgeo::Point3f p5 = {0.5f,-0.5f, 0.5f,1.f};
    pgeo::Point3f p7 = {0.5f, 0.5f, 0.5f,1.f};

    // mut
    pgeo::Plane3f a = pgeo::join(p1,p3,p5);
    pgeo::Plane3f b = pgeo::join(p7,p3,p5);
    print(a, "a");
    print(b, "b");

    EXPECT_EQ(a, b);
}

