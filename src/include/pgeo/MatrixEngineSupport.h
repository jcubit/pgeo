#ifndef PGEOCL_MATRIXENGINESUPPORT_H
#define PGEOCL_MATRIXENGINESUPPORT_H



namespace pgeo {

    namespace detail {

        struct special_ctor_tag{};

    }


    // ------------- helper Concepts -------------------------------------------------------------

    /// Fixed-size engine extent
    template<size_t R, size_t C>
    concept valid_fixed_engine_size = (R > 0 && R != stdex::dynamic_extent)
                                      && (C > 0 && C != stdex::dynamic_extent);

    /// Checks current support of layout
    template<typename L>
    concept valid_layout_for_storage_engine = (std::is_same_v<L, matrix_layout::row_major>
                                               || std::is_same_v<L, matrix_layout::column_major>);


    /// We only consider arithmetic types for the moment.
    /// We can add later complex numbers with their respective conjugate/hermitian operations
    template <typename T>
    concept valid_matrix_elements = std::is_arithmetic_v<T>;


    template<typename T, typename U1, typename U2>
    concept same_as_either = std::same_as<T, U1> or std::same_as<T, U2>;

    // ------------- Subscripts Concepts -------------------------------------------------------------

    ///  This private concept determines whether a given type is equal to one of the three possible
    ///  result types of an engine's const subscript operator.
    template<typename T, typename ET>
    concept valid_const_subscript_result =
    std::same_as<T, typename ET::const_reference>
    or
    std::same_as<T, typename ET::reference>
    or
    std::same_as<T, typename ET::element_type>;

    template<typename ET>
    concept engine_has_valid_2d_const_subscript =
    requires (const ET & engine, typename ET::size_type i)
    {
        { engine(i, i) } -> valid_const_subscript_result<ET>;
    };

    template<typename T, typename ET>
    concept valid_mutable_subscript_result =
    std::same_as<typename ET::reference, typename ET::element_type&>
    and
    std::same_as<T, typename ET::reference>;

    template<typename ET>
    concept engine_has_valid_2d_mutable_subscript =
    requires (ET& engine, typename ET::size_type i)
    {
        { engine(i, i) } -> valid_mutable_subscript_result<ET>;
    };

    /// (Co-)Vector subscripts
    template <typename ET>
    concept engine_has_valid_1d_const_subscript =
    requires (const ET& engine, typename ET::size_type i)
    {
        { engine(i) } -> valid_const_subscript_result<ET>;
    };

    template <typename ET>
    concept engine_has_valid_1d_mutable_subscript =
    requires ( ET& engine, typename ET::size_type i)
    {
        { engine(i) } -> valid_mutable_subscript_result<ET>;
    };


    // ------------- Basic Engine Concepts -------------------------------------------------------------

    template<typename ET>
    concept sizable_engine =
    requires (ET const& engine)
    {
        typename ET::element_type;
        typename ET::size_type;
        typename ET::reference;
        typename ET::const_reference;
        requires std::is_convertible_v<typename ET::reference, typename ET::element_type>;
        requires std::is_convertible_v<typename ET::const_reference, typename ET::element_type>;
        { engine.size()             } -> std::same_as<std::tuple<typename ET::size_type,typename ET::size_type>>;
        { engine.columns()          } -> std::same_as<typename ET::size_type>;
        { engine.rows()             } -> std::same_as<typename ET::size_type>;
    };



    // ------------- Main Engine Concepts -------------------------------------------------------------

    /// Immutable matrix engine
    template <typename ET>
    concept matrix_engine = sizable_engine<ET> and engine_has_valid_2d_const_subscript<ET>;


    /// Mutable matrix engine
    template <typename ET>
    concept mutable_matrix_engine =
    matrix_engine<ET>
    and
    engine_has_valid_2d_mutable_subscript<ET>;

    template<typename ET>
    concept mutable_vector_or_covector_engine =
    mutable_matrix_engine<ET>
    and
    engine_has_valid_1d_const_subscript<ET>
    and
    engine_has_valid_1d_mutable_subscript<ET>;


    /// Owning engine concept: an owning engine is one that owns (manages the lifetime of)
    /// the elements it contains. A matrix view engine is a non-owning engine.
    /// We determine owning engines based on the fact that contains a public nested type alias
    // `owning_engine_type`
    template<typename ET, typename = void>
    struct has_owning_engine_type_alias
            :   public std::false_type
    {
        static constexpr bool   is_owning = true;
        using owning_engine_type = ET;
    };

    template<typename ET>
    struct has_owning_engine_type_alias<ET, std::void_t<typename ET::owning_engine_type>>
    :   public std::true_type
    {
        static constexpr bool   is_owning = false;
        using owning_engine_type = typename ET::owning_engine_type;
    };





    // Helper functions for all matrix engines
    namespace support {

        template<typename ET>
        using get_owning_engine_type_t = typename has_owning_engine_type_alias<ET>::owning_engine_type;

        template<typename ET> inline constexpr
        bool is_owning_engine_type_v = has_owning_engine_type_alias<ET>::is_owning;

        template <typename ET>
        concept owning_matrix_engine_type = is_owning_engine_type_v<ET>;

        // -------------------- layout extractor function ------------------------
        template<typename ET, typename = void>
        struct layout_type_extractor
        {
            using layout_type = matrix_layout::unknown;
        };

        template<typename ET>
        struct layout_type_extractor<ET, std::void_t<typename ET::layout_type>>
        {
            using layout_type = typename ET::layout_type;
        };

        template<typename ET>
        using get_layout_t = typename layout_type_extractor<ET>::layout_type;
        // -------------------- transpose layout getter function ------------------------
        template<class LT>
        struct transpose_layout_helper
        {
            using layout_type = matrix_layout::unknown;
        };

        template<>
        struct transpose_layout_helper<matrix_layout::row_major>
        {
            using layout_type = matrix_layout::column_major;
        };

        template<>
        struct transpose_layout_helper<matrix_layout::column_major>
        {
            using layout_type = matrix_layout::row_major;
        };

        template<class LT>
        using get_transpose_layout_t = typename transpose_layout_helper<LT>::layout_type;

        // ------------------ Check for std vector and array --------------------------------
        template<class T>
        struct is_std_array_or_vector : public std::false_type
        {};

        template<class T, std::size_t N>
        struct is_std_array_or_vector<std::array<T, N>> : public std::true_type
        {};

        template<class T, class A>
        struct is_std_array_or_vector<std::vector<T, A>> : public std::true_type
        {};

        template<class T> inline constexpr
        bool    is_std_array_or_vector_v = is_std_array_or_vector<T>::value;

        // ------------------ constexpr size queries -----------------------------------------
        template<typename N, typename M>
        constexpr bool sizes_differ(N n, M m) noexcept
        {
            using cmp_type = std::common_type_t<N, M, size_t>;

            return (static_cast<cmp_type>(n) != static_cast<cmp_type>(m));
        }


        template<typename ET, typename N, typename M>
        constexpr void verify_engine_size(ET eng, N rows, M cols)
        {
            if (sizes_differ(eng.rows(), rows)) {
                    throw std::runtime_error("number of rows in 2D initialization list does not match destination");
            }
            if (sizes_differ(eng.columns(), cols)){
                throw std::runtime_error("number of columns in 2D initialization list does not match destination");
            }
        }

        template<class T>
        constexpr auto get_list_size(std::initializer_list<std::initializer_list<T>> list)
            -> std::tuple<size_t, size_t>
        {
            size_t  rows = list.size();
            size_t  cols = list.begin()->size();

            for (auto row : list)
            {
                if (row.size() != cols)
                {
                    throw std::runtime_error("Source 2D initializer_list has invalid shape. Not all rows have the same size.");
                }
            }
            return {static_cast<size_t>(rows), static_cast<size_t>(cols)};
        }



        // --- Matrix ---
        /// Copies the matrix elements to the destination type and assigns them
        /// to the destination matrix. The size of the source and destination engine
        /// must match
        template <typename ET1, typename ET2>
        constexpr void
        assign_from(ET1& dst, const ET2& src)
            requires
                mutable_matrix_engine<ET1>
                and
                matrix_engine<ET2>
                and
                std::convertible_to<typename ET2::element_type, typename ET1::element_type>
        {
            using elem_type_dst  = typename ET1::element_type;
            using size_type_dst = typename ET1::size_type;
            using size_type_src = typename ET2::size_type;

            size_type_src  rows = src.rows();
            size_type_src  cols = src.columns();

            verify_engine_size(dst, rows, cols);

            size_type_dst   di = 0;
            size_type_src   si = 0;

            for (; si < rows;  ++di, ++si)
            {
                size_type_dst   dj = 0;
                size_type_src   sj = 0;

                for (; sj < cols;  ++dj, ++sj)
                {
                    dst(di, dj) = static_cast<elem_type_dst>(src(si, sj));
                }
            }
        }

        template<class ET, class U>
        constexpr void assign_from(ET& dst, std::initializer_list<std::initializer_list<U>> src)
        requires mutable_matrix_engine<ET>
                and
                std::convertible_to<U, typename ET::element_type>
        {
            using element_type_dst  = typename ET::element_type;
            using size_type_dst = typename ET::size_type;

            auto    [rows, cols] = get_list_size(src);

            if (sizes_differ(dst.rows(), rows)){
                throw std::runtime_error("number of rows in 2D initialization list does not match destination");
            }
            if (sizes_differ(dst.columns(), cols)){
                throw std::runtime_error("number of columns in 2D initialization list does not match destination");
            }

            size_type_dst   di = 0;
            auto            si = src.begin();

            for (;  di < dst.rows();  ++di, ++si)
            {
                size_type_dst   dj = 0;
                auto            sj = si->begin();

                for (;  dj < dst.columns();  ++dj, ++sj)
                {
                    dst(di, dj) = static_cast<element_type_dst>(*sj);
                }
            }
        }

        /// Vector assignment helper functions
        template <typename ET, typename Container>
        constexpr void
        assign_from(ET& dst,const Container& src)
        requires
            mutable_vector_or_covector_engine<ET>
            and
            std::convertible_to<typename Container::value_type, typename ET::element_type>
        {
            using elem_type_dst  = typename ET::element_type;
            using size_type_dst = typename ET::size_type;
            using size_type_src = typename ET::size_type;

            size_type_dst  rows = dst.rows();
            size_type_dst  cols = dst.columns();

            size_type_dst   dstIndex = 0;
            size_type_src   srcIndex = 0;
            size_type_src   srcSize = src.size();

            if (sizes_differ(rows * cols, srcSize)){
                throw std::runtime_error("destination (co-)vector size does not match source container size");
            }

            for (; srcIndex < srcSize; ++dstIndex, ++srcIndex)
            {
                dst(dstIndex) = static_cast<elem_type_dst>(src[srcIndex]);
            }

        }

        template<class ET, class U>
        constexpr void assign_from(ET& dst, std::initializer_list<U> src)
        requires
            mutable_vector_or_covector_engine<ET>
            and
            std::convertible_to<U, typename ET::element_type>
        {
            using elem_type_dst  = typename ET::element_type;
            using size_type_dst = typename ET::size_type;

            auto    [rows, cols] = dst.size();

            size_type_dst   dstIndex  = 0;
            size_type_dst   dstSize   = rows * cols;
            auto                srcIt = src.begin();

            if (sizes_differ(dstSize, src.size())){
                throw std::runtime_error("destination (co-)vector size does not match source container size");
            }

            for (;  dstIndex < dstSize;  ++dstIndex, ++srcIt)
            {
                dst(dstIndex) = static_cast<elem_type_dst>(*srcIt);
            }
        }


        template<typename ET1, typename ET2>
        constexpr bool are_engines_equal(ET1 const& lhs, ET2 const& rhs)
        requires
        matrix_engine<ET1>
        and
        matrix_engine<ET2>
        and
        std::same_as<typename ET1::element_type, typename ET2::element_type>
        {
            using size_type_lhs = typename ET1::size_type;
            using size_type_rhs = typename ET2::size_type;

            size_type_lhs   r1 = lhs.rows();
            size_type_lhs   c1 = lhs.columns();
            size_type_rhs   r2 = rhs.rows();
            size_type_rhs   c2 = rhs.columns();

            if (sizes_differ(r1, r2) || sizes_differ(c1,c2)) return false;

            size_type_lhs   i1 = 0;
            size_type_rhs   i2 = 0;

            for (;  i1 < r1;  ++i1, ++i2)
            {
                size_type_lhs   j1 = 0;
                size_type_rhs   j2 = 0;

                for (;  j1 < c1;  ++j1, ++j2)
                {
                    if (not (lhs(i1, j1) == rhs(i2, j2))) return false;
                }
            }
            return true;
        }



    } // namespace support


} // namespace pgeo


#endif //PGEOCL_MATRIXENGINESUPPORT_H
