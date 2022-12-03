#ifndef PGEOCL_INTERSECTION_H
#define PGEOCL_INTERSECTION_H

#include <pgeo.h>

namespace pgeo {

    template <typename MT1, typename MT2>
    constexpr Point3<MT1> meet(const Line3<MT1>& line, const Plane3<MT2>& plane)
    {
        detail::get_dual_type_t<MT2> q = {plane.coordinates(0),
                                          plane.coordinates(1),
                                          plane.coordinates(2),
                                          plane.coordinates(3)};
        return line.covariant() * q;
    }

    template <typename MT>
    constexpr auto join(const Line3<MT>& line, const Point3<MT>& point) -> Plane3<detail::get_dual_type_t<MT>>
    {
        return line.contravariant() * point.coordinates;
    }

}

#endif //PGEOCL_INTERSECTION_H
