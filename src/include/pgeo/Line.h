#ifndef PGEOCL_LINE_H
#define PGEOCL_LINE_H

#include <pgeo.h>

namespace pgeo
{

    template <typename T>
    class Line3 {
    public:
        /// starting point
        Point3<T> p;
        /// on-going point
        Point3<T> q;

        using element_type              = T;

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

        template <typename U>
        constexpr Line3(const Point3<U>& p, const Point3<U>& q)
        requires
        valid_matrix_elements<U>
        and
        std::convertible_to<U, element_type>
        : p(p), q(q) {}


        constexpr Mat44<T> covariant() const
        {
            return std::initializer_list<std::initializer_list<T>>
            {{         0           , p(0)*q(1) - p(1)*q(0), p(0)*q(2) - p(2)*q(0), p(0)*q(3) - p(3)*q(0)},
             {p(1)*q(0) - p(0)*q(1),           0          , p(1)*q(2) - p(2)*q(1), p(1)*q(3) - p(3)*q(1)},
             {p(2)*q(0) - p(0)*q(2), p(2)*q(1) - p(1)*q(2),           0          , p(2)*q(3) - p(3)*q(2)},
             {p(3)*q(0) - p(0)*q(3), p(3)*q(1) - p(1)*q(3), p(3)*q(2) - p(2)*q(3),           0          }};

        }


        // ------------------  Modifiers ------------------------------
        constexpr void reverseDirection() noexcept
        {
            std::swap(p,q);
        }

    };

    using Line3f = Line3<float>;
    using Line3d = Line3<double>;

} // namespace pgeo

#endif //PGEOCL_LINE_H
