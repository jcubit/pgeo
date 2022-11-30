#ifndef PGEOCL_JOIN_H
#define PGEOCL_JOIN_H

#include <pgeo.h>

namespace pgeo
{



    namespace detail {

        // --------------------------------------------------------------------------------------------------
        //  Trait:      detect_dual_type<MT>
        //  Alias:      get_dual_type_t<MT>
        //
        //  This private traits type helps to map between dual vector types
        //--------------------------------------------------------------------------------------------------

        // tag for unknown dual type
        struct unknown_dual_type {};

        template<class MT>
        struct detect_dual_type
        {
            using dual_type = unknown_dual_type;
        };

        template<typename T, size_t N>
        struct detect_dual_type<Vec<T,N>>
        {
            using dual_type = CoVec<T,N>;
        };

        template<typename T, size_t N>
        struct detect_dual_type<CoVec<T,N>>
        {
            using dual_type = Vec<T,N>;
        };

        template<typename MT>
        using get_dual_type_t = typename detect_dual_type<MT>::dual_type;

    }




    // ------------------------------------------------------------------------------------

    template <typename MT>
    constexpr auto join(const Point3<MT>& p1, const Point3<MT>& p2, const Point3<MT>& p3)
    -> Plane3<detail::get_dual_type_t<MT>>
    {
        using element_type = typename MT::element_type;
        element_type x = determinant(p1.yzw(), p2.yzw(), p3.yzw());
        element_type y = -determinant(p1.xzw(), p2.xzw(), p3.xzw());
        element_type z = determinant(p1.xyw(), p2.xyw(), p3.xyw());
        element_type w = -determinant(p1.xyz(), p2.xyz(), p3.xyz());

        return {x,y,z,w};
    }

    template <typename MT>
    constexpr auto meet(const Plane3<MT>& p1, const Plane3<MT>& p2, const Plane3<MT>& p3)
    -> Point3<detail::get_dual_type_t<MT>>
    {
        using element_type = typename MT::element_type;
        element_type x = determinant(p1.yzw(), p2.yzw(), p3.yzw());
        element_type y = -determinant(p1.xzw(), p2.xzw(), p3.xzw());
        element_type z = determinant(p1.xyw(), p2.xyw(), p3.xyw());
        element_type w = -determinant(p1.xyz(), p2.xyz(), p3.xyz());

        return {x,y,z,w};
    }

    template <typename MT>
    constexpr auto normalize(const Point3<MT>& p) -> Point3<MT>
    {
        using element_type = typename MT::element_type;
        using coordinate_type = typename MT::coordinate_type;
        element_type w_inv = 1 / p.w();
        coordinate_type coordinates = w_inv * p.coordinates;
        return Point3<MT>(coordinates);
    }


}



#endif //PGEOCL_JOIN_H
