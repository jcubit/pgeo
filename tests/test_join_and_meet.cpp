#include <gtest/gtest.h>

#include "pgeo.h"
#include "utilities.h"


TEST(Point, Meet) {

    pgeo::Plane3f a1 = {0,-1,0,1};
    pgeo::Plane3f a2 = {1,0,0,0};
    pgeo::Plane3f a3 = {0,0,1,0};
    print(a1);

    // mut
    pgeo::Point3f p = pgeo::meet(a1,a2,a3);
    //print(p, "p");


    EXPECT_EQ(p, pgeo::Point3f({0,1,0,1}));

}