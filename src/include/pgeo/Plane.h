#ifndef PGEOCL_PLANE_H
#define PGEOCL_PLANE_H

#include <pgeo.h>

namespace pgeo
{
    /// 3D Plane in homogeneous coordinates
    template<typename MatrixType>
    requires
        coordinate_type<MatrixType>
        and
        match_coordinate_type_v<MatrixType,4>
    class Plane3 {

    public:

        using coordinate_type = MatrixType;
        using element_type    = typename MatrixType::element_type;
        using reference       = element_type&;
        using const_reference = element_type const&;
        using size_type       = typename MatrixType::size_type;

        /// Number of homogeneous coordinates
        static constexpr size_type    coordinates_size   = support::matrix_attributes<MatrixType>::size();
        /// Euclidean dimension
        static constexpr size_type    dimension   = coordinates_size - 1;

        /// homogeneous coordinates of a plane
        coordinate_type                       coordinates;

        // destructor
        ~Plane3() noexcept = default;

        // default constructor
        constexpr Plane3() = default;

        // move constructor
        constexpr Plane3(Plane3&&) noexcept = default;

        // Copy constructor
        constexpr Plane3(Plane3 const&) = default;

        // move assignment
        constexpr Plane3& operator=(Plane3&&) noexcept = default;

        // copy assignment
        constexpr Plane3& operator=(Plane3 const&) = default;

        template<typename U>
        requires
            valid_matrix_elements<U>
            and
            std::convertible_to<U, element_type>
        constexpr Plane3(U x, U y, U z, U w)
        : coordinates({x,y,z,w}) {}

        template<typename U, size_t M>
        requires
            std::convertible_to<U, element_type>
        constexpr Plane3(const CoVec<U,4>& src)
        : coordinates(src) {}

        // Constructor from Point with different type
        template<typename MT2>
        constexpr Plane3(const Plane3<MT2>& src)
        requires
            is_point3_coordinates<MT2>
            and
            std::convertible_to<typename MT2::element_type, element_type>
        : coordinates(src.coordinates) {}


        // Constructors from std::array or std::vector
        template<typename Container>
        constexpr explicit Plane3(const Container& src)
                :   coordinates(src) {}

        // Constructor from initialization list
        template<typename U>
        constexpr Plane3(std::initializer_list<U> src)
                :   coordinates(src) {}

        // Assignment from Point with different type
        template <typename MT2>
        constexpr Plane3& operator=(Plane3<MT2> const& rhs)
        requires
            is_point3_coordinates<MT2>
            and
            std::convertible_to<typename MT2::element_type, element_type>
        {
            coordinates(rhs.coordinates);
            return *this;
        }

        // Assignment with std::array or std::vector (with type conversion)
        template<typename Container>
        constexpr Plane3& operator =(Container const& rhs)
        {
            coordinates(rhs.coordinates);
            return *this;
        }

        // Assignment from initialization list
        template<typename U>
        constexpr Plane3& operator =(std::initializer_list<U> rhs)
        {
            coordinates(rhs.coordinates);
            return *this;
        }

        // ------------------  Size --------------------------------
        constexpr size_type size() const noexcept
        {
            return coordinates_size;
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
        { return coordinates(1); }

        constexpr element_type z() const
        { return coordinates(2); }

        constexpr element_type w() const
        { return coordinates(dimension); }

        constexpr Vec<element_type ,3> xyz() const
        {
            return {coordinates(0), coordinates(1), coordinates(2)};
        }

        constexpr Vec<element_type ,3> yzw() const
        {
            return {coordinates(1), coordinates(2), coordinates(3)};
        }

        constexpr Vec<element_type ,3> xzw() const
        {
            return {coordinates(0), coordinates(2), coordinates(3)};
        }

        constexpr Vec<element_type,3> xyw() const
        {
            return {coordinates(0), coordinates(1), coordinates(3)};
        }

        // ------------------  Modifiers  --------------------------
        constexpr void normalize() noexcept
        {
            element_type w_inv = 1. / w();
            coordinates = w_inv * coordinates;
        }


    }; // class Plane

    template <typename T>
    using Plane3Base = Plane3<CoVec<T,4>>;

    using Plane3i = Plane3Base<int32_t>;
    using Plane3f = Plane3Base<float>;
    using Plane3d = Plane3Base<double>;


    // -------------- Projective Equality Comparison ------------------------------------------------------

    template <typename MT1, typename MT2>
    constexpr bool operator==(Plane3<MT1> const& lhs, Plane3<MT2> const& rhs)
    {
        Plane3<MT1> to_be_normalized_lhs = lhs;
        Plane3<MT2> to_be_normalized_rhs = rhs;
        to_be_normalized_lhs.normalize();
        to_be_normalized_rhs.normalize();
        return to_be_normalized_lhs.coordinates == to_be_normalized_rhs.coordinates;
    }

    template <typename ET1, typename ET2>
    constexpr bool operator!=(Plane3<ET1> const& lhs, Plane3<ET2> const& rhs)
    {
        return !(lhs == rhs);
    }


} // namespace pgeo

#endif //PGEOCL_PLANE_H
