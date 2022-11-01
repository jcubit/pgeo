#ifndef PGEOCL_UTILITIES_H
#define PGEOCL_UTILITIES_H

#include "pgeo.h"
#include "spdlog/spdlog.h"

template <typename T>
void print(pgeo::Mat22<T> m)
{
    spdlog::info("({}, {}, \n {}, {})", m(0,0),m(0,1),m(1,0), m(1,1));
}

#endif //PGEOCL_UTILITIES_H
