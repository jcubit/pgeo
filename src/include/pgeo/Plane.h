#ifndef PGEOCL_PLANE_H
#define PGEOCL_PLANE_H

#include <pgeo.h>

namespace pgeo
{
    // TODO: Add Point Concept: It has Vec<T,N> as coordinates and N > 1

    // Points store coordinates in a column vector
    template<typename T, size_t N>
    requires valid_point_size<N>
    class Plane {

    public:

        /// homogeneous coordinates of a plane
        CoVec<T,N>                        coordinates;

        /// Euclidean dimension
        static constexpr size_t     dimension   = N-1;

        using element_type    = T;
        using reference       = element_type&;
        using const_reference = element_type const&;
        using size_type       = size_t;

        // destructor
        ~Plane() noexcept = default;

        // default constructor
        constexpr Plane() = default;

        // move constructor
        constexpr Plane(Plane&&) noexcept = default;

        // Copy constructor
        constexpr Plane(Plane const&) = default;

        // move assignment
        constexpr Plane& operator=(Plane&&) noexcept = default;

        // copy assignment
        constexpr Plane& operator=(Plane const&) = default;

        // Constructor from Point with different type
        template<typename U, size_t M>
        constexpr Plane(const Plane<U,M>& src)
        requires
        same_point_size<M,N>
        and
        std::convertible_to<U, element_type>
                : coordinates(src.coordinates) {}


        // Constructors from std::array or std::vector
        template<typename Container>
        constexpr explicit Plane(const Container& src)
                :   coordinates(src) {}

        // Constructor from initialization list
        template<typename U>
        constexpr Plane(std::initializer_list<U> src)
                :   coordinates(src) {}

        // Assignment from Point with different type
        template <typename U, size_t M>
        constexpr Plane& operator=(Plane<U,M> const& rhs)
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
        constexpr Plane& operator =(Container const& rhs)
        {
            coordinates(rhs.coordinates);
            return *this;
        }

        // Assignment from initialization list
        template<typename U>
        constexpr Plane& operator =(std::initializer_list<U> rhs)
        {
            coordinates(rhs.coordinates);
            return *this;
        }

//        // ------------------  Constructor from Points --------------------------------
//        template <typename U, size_t M>
//        requires std::is_convertible_v<U,element_type>
//        constexpr Plane(const Point<U,M>& p1, const Point<U,M>& p2, const Point<U,M>& p3)
//        {
//            element_type x = determinant(p1.yzw(), p2.yzw(), p3.yzw());
//            element_type y = -determinant(p1.xzw(), p2.xzw(), p3.xzw());
//            element_type z = determinant(p1.xyw(), p2.xyw(), p3.xyw());
//            element_type w = -determinant(p1.xyz(), p2.xyz(), p3.xyz());
//
//            coordinates = {x,y,z,w};
//        }

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
            return {coordinates(0),coordinates(1), coordinates(2)};
        }

        constexpr Vec<T,3> yzw() const
        requires at_least_size_four<N>
        {
            return {coordinates(1),coordinates(2), coordinates(3)};
        }

        constexpr Vec<T,3> xzw() const
        requires at_least_size_four<N>
        {
            return {coordinates(0),coordinates(2), coordinates(3)};
        }

        constexpr Vec<T,3> xyw() const
        requires at_least_size_four<N>
        {
            return {coordinates(0),coordinates(1), coordinates(3)};
        }

        // ------------------  Modifiers  --------------------------
        constexpr void normalize() noexcept
        {
            element_type w_inv = 1. / w();
            coordinates = w_inv * coordinates;
        }


    }; // class Plane

    template <typename T>
    using Plane3 = Plane<T,4>;

    using Plane3i = Plane3<int32_t>;
    using Plane3f = Plane3<float>;
    using Plane3d = Plane3<double>;


    // -------------- Equality Comparison ------------------------------------------------------

    template <typename T, size_t N, typename U, size_t M>
    constexpr bool operator==(Plane<T,N> const& lhs, Plane<U,M> const& rhs)
    {
        return lhs.coordinates == rhs.coordinates;
    }

    template <typename T, size_t N, typename U, size_t M>
    constexpr bool operator!=(Plane<T,N> const& lhs, Plane<U,M> const& rhs)
    {
        return !(lhs.coordinates == rhs.coordinates);
    }


} // namespace pgeo

#endif //PGEOCL_PLANE_H