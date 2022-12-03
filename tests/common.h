#ifndef PGEOCL_COMMON_H
#define PGEOCL_COMMON_H

#include <vector>
#include "pgeo.h"

template <typename T>
struct Cube {

    const std::array<pgeo::Point3Base<T>,8> corners{{pgeo::Point3Base<T>(-0.5, -0.5, -0.5, 1.),
                                                     pgeo::Point3Base<T>( 0.5, -0.5, -0.5, 1.),
                                                     pgeo::Point3Base<T>(-0.5,  0.5, -0.5, 1.),
                                                     pgeo::Point3Base<T>( 0.5,  0.5, -0.5, 1.),
                                                     pgeo::Point3Base<T>(-0.5, -0.5,  0.5, 1.),
                                                     pgeo::Point3Base<T>( 0.5, -0.5,  0.5, 1.),
                                                     pgeo::Point3Base<T>(-0.5,  0.5,  0.5, 1.),
                                                     pgeo::Point3Base<T>( 0.5,  0.5,  0.5, 1.)}};

    const pgeo::Mat<uint32_t, 6,4> cubeIndices = {{0,4,6,2},
                                                  {1,3,7,5},
                                                  {0,1,5,4},
                                                  {2,6,7,3},
                                                  {0,2,3,1},
                                                  {4,5,7,6}};


    const pgeo::Point3Base<T>& operator()(uint i) const {return corners[i]; }

};


#endif //PGEOCL_COMMON_H
