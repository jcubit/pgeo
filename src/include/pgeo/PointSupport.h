#ifndef PGEOCL_POINTSUPPORT_H
#define PGEOCL_POINTSUPPORT_H

namespace pgeo
{
    // ------------- helper Concepts -------------------------------------------------------------

    /// point size
    template<size_t N>
    concept valid_point_size = (N > 1);

    template<size_t N>
    concept at_least_size_three = (N > 2);

    template<size_t N>
    concept at_least_size_four = (N > 3);

    template<size_t N, size_t M>
    concept same_point_size = (N == M);

    // ------------- 1D Matrix and 1D Engine Concepts -------------------------------------------------------------

    template <typename T>
    struct is_vector : public std::false_type { };

    template <typename T, size_t R, typename L>
    struct is_vector<Matrix<MatrixEngine<T,R,1,L>>> : public std::true_type { };

    template<typename T>
    inline constexpr bool    is_vector_v = is_vector<T>::value;

    template <typename T>
    struct is_co_vector : public std::false_type { };

    template <typename T, size_t C, typename L>
    struct is_co_vector<Matrix<MatrixEngine<T,1,C,L>>> : public std::true_type { };

    template<typename T>
    inline constexpr bool    is_co_vector_v = is_co_vector<T>::value;

    template<typename T>
    concept one_dimensional_matrix = is_vector_v<T> || is_co_vector_v<T>;



    // ------------- Basic Point Concepts -------------------------------------------------------------

    template<typename PointType>
    concept sizable_point =
    requires (const PointType & point)
    {
        typename PointType::element_type;
        typename PointType::size_type;
        typename PointType::reference;
        typename PointType::const_reference;
        requires std::is_convertible_v<typename PointType::reference, typename PointType::element_type>;
        requires std::is_convertible_v<typename PointType::const_reference, typename PointType::element_type>;
        { point.size()             } -> std::same_as<typename PointType::size_type>;
    };



    // ------------- Main Point Concepts -------------------------------------------------------------

    /// main point concept
    template <typename PointType>
    concept point = sizable_point<PointType>;


    // ------------- Subscripts Concepts -------------------------------------------------------------


    namespace support
    {

    }
}


#endif //PGEOCL_POINTSUPPORT_H
