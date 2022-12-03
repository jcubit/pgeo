#ifndef PGEOCL_SIDEWRAP_H
#define PGEOCL_SIDEWRAP_H

#include <pgeo.h>

namespace pgeo
{
    template <typename MT>
    constexpr auto sideWrap(const Line3<MT>& l1, const Line3<MT>& l2) -> typename MT::element_type
    {
        return -determinant(l1.p.coordinates,
                           l1.q.coordinates,
                           l2.p.coordinates,
                           l2.q.coordinates);
//        using element_type = typename MT::element_type;
//        Mat44<element_type> A_t = l1.covariant().t();
//        Mat44<element_type> B = l2.contraVariant();
//
//        return pgeo::innerProduct(A_t,B);

    }


} // namespace pgeo

#endif //PGEOCL_SIDEWRAP_H
