#ifndef PGEOCL_UTILITIES_H
#define PGEOCL_UTILITIES_H

#include "pgeo.h"
#include "spdlog/spdlog.h"

template <typename T>
void print(pgeo::Mat22<T> m)
{
    spdlog::info("\n({}, {}, \n {}, {})", m(0,0),m(0,1),m(1,0), m(1,1));
}

template <typename T>
void print(pgeo::Mat33<T> m)
{
    spdlog::info("\n({}, {}, {}, \n {}, {}, {}\n {}, {}, {})",
                 m(0,0),m(0,1),m(0,2),
                 m(1,0), m(1,1), m(1,2),
                 m(2,0), m(2,1), m(2,2));
}

#endif //PGEOCL_UTILITIES_H
