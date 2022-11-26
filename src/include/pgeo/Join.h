#ifndef PGEOCL_JOIN_H
#define PGEOCL_JOIN_H

#include <pgeo.h>

namespace pgeo
{

    template <typename T, size_t N>
    constexpr auto join(const Point<T,N>& p1, const Point<T,N>& p2, const Point<T,N>& p3) -> Plane<T,N>
    {
        T x = determinant(p1.yzw(), p2.yzw(), p3.yzw());
        T y = -determinant(p1.xzw(), p2.xzw(), p3.xzw());
        T z = determinant(p1.xyw(), p2.xyw(), p3.xyw());
        T w = -determinant(p1.xyz(), p2.xyz(), p3.xyz());

        return {x,y,z,w};
    }

    template <typename T, size_t N>
    constexpr auto meet(const Plane<T,N>& p1, const Plane<T,N>& p2, const Plane<T,N>& p3) -> Point<T,N>
    {
        T x = determinant(p1.yzw(), p2.yzw(), p3.yzw());
        T y = -determinant(p1.xzw(), p2.xzw(), p3.xzw());
        T z = determinant(p1.xyw(), p2.xyw(), p3.xyw());
        T w = -determinant(p1.xyz(), p2.xyz(), p3.xyz());

        return {x,y,z,w};
    }

    template <typename T, size_t N>
    constexpr auto normalize(const Point<T,N>& p) -> Point<T,N>
    {
        T w_inv = 1 / p.w();
        Vec<T,N> coordinates = w_inv * p.coordinates;
        return Point<T,N>(coordinates);
    }


}



#endif //PGEOCL_JOIN_H
