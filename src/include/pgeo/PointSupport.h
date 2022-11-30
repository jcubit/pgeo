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

    // --------------------------------------------------------------------------------------------------
    //  Trait:      is_valid_vector_engine<ET>
    //  Variables:  is_valid_vector_engine_v<ET>
    //  Concept:    vector_engine<ET>
    //
    //  This traits type is used to validate that the engine has a one-dimensional extent. Either the rows
    //  must be one or the number of columns is one.
    //--------------------------------------------------------------------------------------------------

    template<vector_or_covector_engine ET>
    struct is_valid_vector_engine
    {
        static constexpr bool   value =
                ((ET::rows_ > 0) && (ET::cols_ == 1)) ||  ((ET::rows_ == 1) && (ET::cols_ > 0));
    };

    template<vector_or_covector_engine T>
    inline constexpr bool    is_valid_vector_engine_v = is_valid_vector_engine<T>::value;

    template <typename ET>
    concept vector_engine = is_valid_vector_engine_v<ET>;

    // --------------------------------------------------------------------------------------------------
    //  Trait:      has_valid_target_engine_size<ET>
    //  Variables:  has_valid_target_engine_size_v<ET>
    //
    //  This traits type is used to validate that the engine size is the required.
    //--------------------------------------------------------------------------------------------------

    //
    template <typename ET, size_t N>
    struct has_valid_target_engine_size
    {
        static constexpr size_t size = ET::rows_ * ET::cols_;
        static constexpr bool   value = !support::sizes_differ(size,N);
    };

    template <typename ET, size_t N>
    inline constexpr bool has_valid_target_engine_size_v = has_valid_target_engine_size<ET,N>::value;


    // --------------------------------------------------------------------------------------------------
    //  Trait:      is_valid_coordinate_type<MT>
    //  Variables:  is_valid_coordinate_type_v<MT>
    //  Concept:    coordinate_type<ET>
    //
    //  This traits type is used to validate that the template matrix type is a valid type for the
    //  coordinates of a Point class
    //--------------------------------------------------------------------------------------------------
    template <typename MT>
    struct is_valid_coordinate_type
    {
        using engine_type = typename MT::owning_engine_type;
        static constexpr bool   value = is_valid_vector_engine_v<engine_type>;
    };

    template <typename T>
    inline constexpr bool is_valid_coordinate_type_v = is_valid_coordinate_type<T>::value;

    template <typename T>
    concept coordinate_type = is_valid_coordinate_type_v<T>;

    // --------------------------------------------------------------------------------------------------
    //  Trait:      match_coordinate_type<MT>
    //  Variables:  match_coordinate_type_v<MT>
    //
    //  This traits type is used to validate that the source template matrix type has a valid size
    //  for the target point class
    //--------------------------------------------------------------------------------------------------
    template <typename MT, size_t N>
    struct match_coordinate_type
    {
        using engine_type = typename MT::owning_engine_type;
        static constexpr bool   value = has_valid_target_engine_size_v<engine_type,N>;
    };

    template <typename T, size_t N>
    inline constexpr bool match_coordinate_type_v = match_coordinate_type<T,N>::value;

    // ------------- Main Point Concepts -------------------------------------------------------------

    /// Main point3 concept has to have
    /// - valid one dimensional matrix as coordinate type
    template <typename MT>
    concept is_point3_coordinates = coordinate_type<MT> and match_coordinate_type_v<MT,4>;


    // ------------- Subscripts Concepts -------------------------------------------------------------


    namespace support
    {
        template <coordinate_type MT>
        struct matrix_attributes
        {
            static constexpr size_t rows()
            {
                using engine_type = typename MT::owning_engine_type;
                return engine_type::rows_;
            }

            static constexpr size_t columns()
            {
                using engine_type = typename MT::owning_engine_type;
                return engine_type::cols_;
            }

            static constexpr size_t size()
            {
                using engine_type = typename MT::owning_engine_type;
                return rows() * columns();
            }
        };



    }
}


#endif //PGEOCL_POINTSUPPORT_H
