#ifndef PGEOCL_POINT_H
#define PGEOCL_POINT_H

#include <pgeo.h>

namespace pgeo
{

    // TODO: Add Point Concept: It has Vec<T,N> as coordinates and N > 1

    // Points store coordinates in a column vector
    template<typename T, size_t N>
    requires valid_point_size<N>
    class Point {

    public:

        /// homogeneous coordinates of a point
        Vec<T,N>                        coordinates;

        /// Euclidean dimension
        static constexpr size_t     dimension   = N-1;

        using element_type    = T;
        using reference       = element_type&;
        using const_reference = element_type const&;
        using size_type       = size_t;

        // destructor
        ~Point() noexcept = default;

        // default constructor
        constexpr Point() = default;

        // move constructor
        constexpr Point(Point&&) noexcept = default;

        // Copy constructor
        constexpr Point(Point const&) = default;

        // move assignment
        constexpr Point& operator=(Point&&) noexcept = default;

        // copy assignment
        constexpr Point& operator=(Point const&) = default;

        // Constructor from Point with different type
        template<typename U, size_t M>
        constexpr Point(const Point<U,M>& src)
        requires
        (not support::sizes_differ<M,N>)
        and
        std::convertible_to<U, element_type>
                : coordinates(src.coordinates) {}


        // Constructors from std::array or std::vector
        template<typename Container>
        constexpr explicit Point(const Container& src)
                :   coordinates(src) {}

        // Constructor from initialization list
        template<typename U>
        constexpr Point(std::initializer_list<U> src)
                :   coordinates(src) {}

        // Assignment from Point with different type
        template <typename U, size_t M>
        constexpr Point& operator=(Point<U,M> const& rhs)
        requires
        same_point_size<M,N>
        and
        std::convertible_to<U, element_type>
        {
            coordinates(rhs.coordinates);
            return *this;
        }

        // Assignment with std::array or std::vector (with type conversion)
        template<typename Container>
        constexpr Point& operator =(Container const& rhs)
        {
            coordinates(rhs.coordinates);
            return *this;
        }

        // Assignment from initialization list
        template<typename U>
        constexpr Point& operator =(std::initializer_list<U> rhs)
        {
            coordinates(rhs.coordinates);
            return *this;
        }
        

        // ------------------  Size --------------------------------
        constexpr size_type size() const noexcept
        {
            return N;
        }

        constexpr size_type dim() const noexcept
        {
            return dimension;
        }

        // ------------------  Element access --------------------------
        constexpr reference operator()(size_type i)
        {
            return coordinates(i);
        }

        constexpr const_reference operator()(size_type i) const
        {
            return coordinates(i);
        }

        constexpr element_type x() const { return coordinates(0); }

        constexpr element_type y() const
        requires at_least_size_three<N>
        { return coordinates(1); }

        constexpr element_type z() const
        requires at_least_size_four<N>
        { return coordinates(2); }

        constexpr element_type w() const
        { return coordinates(dimension); }

        constexpr Vec<T,3> xyz() const
        requires at_least_size_four<N>
        {
            return {coordinates(0), coordinates(1), coordinates(2)};
        }

        constexpr Vec<T,3> yzw() const
        requires at_least_size_four<N>
        {
            return {coordinates(1), coordinates(2), coordinates(3)};
        }

        constexpr Vec<T,3> xzw() const
        requires at_least_size_four<N>
        {
            return {coordinates(0), coordinates(2), coordinates(3)};
        }

        constexpr Vec<T,3> xyw() const
        requires at_least_size_four<N>
        {
            return {coordinates(0), coordinates(1), coordinates(3)};
        }

        // ------------------  Modifiers  --------------------------
        constexpr void normalize() noexcept
        {
            element_type w_inv = 1. / w();
            coordinates = w_inv * coordinates;
        }



    }; // class Point

    template <typename T>
    using Point3 = Point<T,4>;

    using Point3i = Point3<int32_t>;
    using Point3f = Point3<float>;
    using Point3d = Point3<double>;


    // -------------- Equality Comparison ------------------------------------------------------

    template <typename T, size_t N, typename U, size_t M>
    constexpr bool operator==(Point<T,N> const& lhs, Point<U,M> const& rhs)
    {
        Point<T,N> to_be_normalized_lhs = lhs;
        Point<T,N> to_be_normalized_rhs = rhs;
        to_be_normalized_lhs.normalize();
        to_be_normalized_rhs.normalize();
        return to_be_normalized_lhs.coordinates == to_be_normalized_rhs.coordinates;
    }

    template <typename T, size_t N, typename U, size_t M>
    constexpr bool operator!=(Point<T,N> const& lhs, Point<U,M> const& rhs)
    {
        return !(lhs.coordinates == rhs.coordinates);
    }


} // namespace pgeo

#endif //PGEOCL_POINT_H

