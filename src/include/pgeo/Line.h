#ifndef PGEOCL_LINE_H
#define PGEOCL_LINE_H

#include <pgeo.h>

namespace pgeo
{

    template <typename MT>
    class Line3 {
    public:
        /// starting point
        Point3<MT> p;
        /// on-going point
        Point3<MT> q;

        using element_type              = typename MT::element_type;

        // destructor
        ~Line3() noexcept = default;

        // default constructor
        constexpr Line3() = default;

        // move constructor
        constexpr Line3(Line3&&) noexcept = default;

        // Copy constructor
        constexpr Line3(const Line3 &) = default;

        // move assignment
        constexpr Line3& operator=(Line3&&) noexcept = default;

        // copy assignment
        constexpr Line3& operator=(const Line3 &) = default;

        template <typename MT2>
        constexpr Line3(const Point3<MT2>& p, const Point3<MT2>& q)
        requires
        std::convertible_to<typename MT2::element_type, element_type>
        : p(p), q(q) {}


        constexpr Mat44<element_type> covariant() const
        {
            return std::initializer_list<std::initializer_list<element_type>>
            {{         0           , p(0)*q(1) - p(1)*q(0), p(0)*q(2) - p(2)*q(0), p(0)*q(3) - p(3)*q(0)},
             {p(1)*q(0) - p(0)*q(1),           0          , p(1)*q(2) - p(2)*q(1), p(1)*q(3) - p(3)*q(1)},
             {p(2)*q(0) - p(0)*q(2), p(2)*q(1) - p(1)*q(2),           0          , p(2)*q(3) - p(3)*q(2)},
             {p(3)*q(0) - p(0)*q(3), p(3)*q(1) - p(1)*q(3), p(3)*q(2) - p(2)*q(3),           0          }};

        }

        constexpr Mat44<element_type> contravariant() const
        {
            return std::initializer_list<std::initializer_list<element_type>>
                    {{         0           , p(3)*q(2) - p(2)*q(3), p(1)*q(3) - p(3)*q(1), p(2)*q(1) - p(1)*q(2)},
                     {p(2)*q(3) - p(3)*q(2),           0          , p(3)*q(0) - p(0)*q(3), p(0)*q(2) - p(2)*q(0)},
                     {p(3)*q(1) - p(1)*q(3), p(0)*q(3) - p(3)*q(0),           0          , p(1)*q(0) - p(0)*q(1)},
                     {p(1)*q(2) - p(2)*q(1), p(2)*q(0) - p(0)*q(2), p(0)*q(1) - p(1)*q(0),           0          }};

        }


        // ------------------  Modifiers ------------------------------
        constexpr void reverseDirection() noexcept
        {
            std::swap(p,q);
        }

    };

    using Line3f = Line3<Vec<float,4>>;
    using Line3d = Line3<Vec<double,4>>;

} // namespace pgeo

#endif //PGEOCL_LINE_H
