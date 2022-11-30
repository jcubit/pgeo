#ifndef PGEOCL_POINT_H
#define PGEOCL_POINT_H

#include <pgeo.h>

namespace pgeo
{
    /// Points in homogeneous coordinates
    template<typename MatrixType>
    requires
        coordinate_type<MatrixType>
        and
        match_coordinate_type_v<MatrixType,4>
    class Point3 {

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

        /// homogeneous coordinates of a point
        coordinate_type                        coordinates;

        // destructor
        ~Point3() noexcept = default;

        // default constructor
        constexpr Point3() = default;

        // move constructor
        constexpr Point3(Point3&&) noexcept = default;

        // Copy constructor
        constexpr Point3(Point3 const&) = default;

        // move assignment
        constexpr Point3& operator=(Point3&&) noexcept = default;

        // copy assignment
        constexpr Point3& operator=(Point3 const&) = default;


        template<typename U>
        requires
            valid_matrix_elements<U>
            and
            std::convertible_to<U, element_type>
        constexpr Point3(U x, U y, U z, U w)
        : coordinates({ x, y, z, w}) {}

        template<typename U, size_t M>
        requires
            std::convertible_to<U, element_type>
        constexpr Point3(const Vec<U,4>& src)
        : coordinates(src) {}


        // Constructor from Point with different type
        template<typename MT2>
        constexpr Point3(const Point3<MT2>& src)
        requires
            is_point3_coordinates<MT2>
            and
            std::convertible_to<typename MT2::element_type, element_type>
        : coordinates(src.coordinates) {}


        // Constructors from std::array or std::vector
        template<typename Container>
        constexpr explicit Point3(const Container& src)
        :   coordinates(src) {}

        // Constructor from initialization list
        template<typename U>
        constexpr Point3(std::initializer_list<U> src)
                :   coordinates(src) {}

        // Assignment from Point with different type
        template <typename MT2>
        constexpr Point3& operator=(Point3<MT2> const& rhs)
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
        constexpr Point3& operator =(Container const& rhs)
        {
            coordinates(rhs.coordinates);
            return *this;
        }

        // Assignment from initialization list
        template<typename U>
        constexpr Point3& operator =(std::initializer_list<U> rhs)
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

        constexpr Vec<element_type ,3> xyw() const
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
    using Point3Base = Point3<Vec<T,4>>;

    using Point3i = Point3Base<int32_t>;
    using Point3f = Point3Base<float>;
    using Point3d = Point3Base<double>;


    // -------------- Projective Equality Comparison ------------------------------------------------------

    template <typename ET1, typename ET2>
    constexpr bool operator==(Point3<ET1> const& lhs, Point3<ET2> const& rhs)
    {
        Point3<ET1> to_be_normalized_lhs = lhs;
        Point3<ET2> to_be_normalized_rhs = rhs;
        to_be_normalized_lhs.normalize();
        to_be_normalized_rhs.normalize();
        return to_be_normalized_lhs.coordinates == to_be_normalized_rhs.coordinates;
    }

    template <typename ET1, typename ET2>
    constexpr bool operator!=(Point3<ET1> const& lhs, Point3<ET2> const& rhs)
    {
        Point3<ET1> to_be_normalized_lhs = lhs;
        Point3<ET2> to_be_normalized_rhs = rhs;
        to_be_normalized_lhs.normalize();
        to_be_normalized_rhs.normalize();
        return !(to_be_normalized_lhs.coordinates == to_be_normalized_rhs.coordinates);
    }


} // namespace pgeo

#endif //PGEOCL_POINT_H

