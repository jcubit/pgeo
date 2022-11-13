#ifndef PGEOCL_MATRIX_H
#define PGEOCL_MATRIX_H

#include <pgeo.h>

namespace pgeo {

    template <typename EngineType>
    requires std::default_initializable<EngineType>
            and
            std::copyable<EngineType>
            and
            matrix_engine<EngineType>
    class Matrix {

        static constexpr bool   is_writable = mutable_matrix_engine<EngineType>;

        // helper tags for modifying the return type of the matrix views
        using possibly_writable_submatrix = std::conditional_t<is_writable,matrix_view::submatrix, matrix_view::const_submatrix>;
        using possibly_writable_transpose = std::conditional_t<is_writable, matrix_view::transpose, matrix_view::const_transpose>;


    public:


        using owning_engine_type        = support::get_owning_engine_type_t<EngineType>;
        using element_type              = typename EngineType::element_type;
        using reference                 = typename EngineType::reference;
        using const_reference           = typename EngineType::const_reference;
        using size_type                 = typename EngineType::size_type;

        // TODO: does there exist a matrix which does not have a span, e.g. should view matrices have spans?
        using span_type					= typename EngineType::span_type;
        using const_span_type			= typename EngineType::const_span_type;

        // Type aliases for matrix views
        using submatrix_type            = Matrix<MatrixViewEngine<EngineType, possibly_writable_submatrix>>;
        using const_submatrix_type      = Matrix<MatrixViewEngine<EngineType, matrix_view::const_submatrix>>;
        using transpose_type            = Matrix<MatrixViewEngine<EngineType, possibly_writable_transpose>>;
        using const_transpose_type      = Matrix<MatrixViewEngine<EngineType, matrix_view::const_transpose>>;




        // destructor
        ~Matrix() noexcept = default;

        // default constructor
        constexpr Matrix() = default;

        // move constructor
        constexpr Matrix(Matrix&&) noexcept = default;

        // Copy constructor
        constexpr Matrix(Matrix const&) = default;

        /// constructor from different engine, but constructible from
        /// the current engine
        template <typename EngineType2>
        constexpr Matrix(Matrix<EngineType2> const& src)
        requires
            mutable_matrix_engine<EngineType>
            and
            std::constructible_from<EngineType, EngineType2>
        : engine_(src.engine_) {}

        /// Constructor from different engine and not constructible from
        /// the current engine
        template <typename EngineType2>
        constexpr Matrix(Matrix<EngineType2> const& src)
        requires
            mutable_matrix_engine<EngineType>
            and
            (not std::constructible_from<EngineType, EngineType2>)
            and
            std::convertible_to<typename EngineType2::element_type, element_type>
        : engine_()
        {
            support::assign_from(engine_, src.engine_);
        }

        /// Constructor with initialization list (without type conversion)
        template<typename T2>
        constexpr Matrix(std::initializer_list<std::initializer_list<T2>> listOfRows)
        requires
            mutable_matrix_engine<EngineType>
            and
            std::constructible_from<EngineType, decltype(listOfRows)>
        : engine_(listOfRows) {}

        /// Constructor with initialization list and type conversion
        template<typename T2>
        constexpr Matrix(std::initializer_list<std::initializer_list<T2>> listOfRows)
        requires
        mutable_matrix_engine<EngineType>
        and
        (not std::constructible_from<EngineType, decltype(listOfRows)>)
        and
        std::convertible_to<T2, element_type>
        {
            support::assign_from(engine_, listOfRows);
        }

        // move assignment
        constexpr Matrix& operator=(Matrix&&) noexcept = default;

        // copy assignment
        constexpr Matrix& operator=(Matrix const&) = default;

        // Assignment directly from different engine
        template <typename EngineType2>
        constexpr Matrix& operator=(Matrix<EngineType2> const& rhs)
        requires
            mutable_matrix_engine<EngineType>
            and
            std::assignable_from<EngineType, EngineType2>
        {
            engine_ = rhs.engine();
            return *this;
        }

        // Assignment from different non-assignable engine with type conversion
        template <typename EngineType2>
        constexpr Matrix& operator=(Matrix<EngineType2> const& rhs)
        requires
            mutable_matrix_engine<EngineType>
            and
            (not std::assignable_from<EngineType, EngineType2>)
            and
            std::convertible_to<typename EngineType2::element_type, element_type>
        {
            support::assign_from(engine_, rhs);
            return *this;
        }

        // Assignment with initialization list (with type conversion)
        template<typename T2>
        constexpr Matrix& operator=(std::initializer_list<std::initializer_list<T2>> listOfRows)
        requires
            mutable_matrix_engine<EngineType>
            and
            std::assignable_from<EngineType, decltype(listOfRows)>
        {
            engine_ = listOfRows;
            return *this;
        }

        // Assignment with initialization list (with type conversion)
        template<typename T2>
        constexpr Matrix& operator=(std::initializer_list<std::initializer_list<T2>> listOfRows)
        requires
            mutable_matrix_engine<EngineType>
            and
            (not std::assignable_from<EngineType, decltype(listOfRows)>)
            and
            std::convertible_to<T2, element_type>
        {
            support::assign_from(engine_, listOfRows);
            return *this;
        }



        // ------------------  Capacity --------------------------------

        constexpr size_type columns() const noexcept
        {
            return engine_.columns();
        }
        constexpr size_type rows() const noexcept
        {
            return engine_.rows();
        }
        constexpr std::tuple<size_type, size_type> size() const noexcept
        {
            return engine_.size();
        }

        // ------------------  Element access --------------------------

        constexpr reference			operator()(size_type i, size_type j)
        {
            return engine_(i,j);
        }
        constexpr const_reference	operator()(size_type i, size_type j) const
        {
            return engine_(i,j);
        }

        // TODO: complete the implementation of these views
        constexpr submatrix_type        submatrix(size_type rowStart, size_type rowStep,
                                                  size_type colStart, size_type colStep) noexcept
        {
            return submatrix_type(detail::special_ctor_tag(), engine_, rowStart, rowStep, colStart, colStep);
        }
        constexpr const_submatrix_type  submatrix(size_type rowStart, size_type rowStep,
                                                  size_type colStart, size_type colStep) const noexcept
        {
            return const_submatrix_type(detail::special_ctor_tag(), engine_, rowStart, rowStep, colStart, colStep);
        }
        constexpr transpose_type			t()
        {
            return transpose_type (detail::special_ctor_tag(), engine_);
        }
        constexpr const_transpose_type		t() const
        {
            return const_transpose_type (detail::special_ctor_tag(), engine_);
        }

        // ------------------  Data access ----------------------------

        constexpr EngineType&			engine() noexcept { return engine_; }
        constexpr EngineType const&	engine() const noexcept { return engine_; }

        constexpr span_type			span() noexcept { return engine_.span(); }
        constexpr const_span_type	span() const noexcept { return engine_.span(); }

        // ------------------  Modifiers ------------------------------

        constexpr void swap(Matrix& rhs) noexcept
        {
            engine_.swap(rhs.engine_);
        }
        constexpr void swapColumns(size_type col1, size_type col2) noexcept
        {
            engine_.swapColumns(col1, col2);
        }
        constexpr void swapRows(size_type row1, size_type row2) noexcept
        {
            engine_.swapRows(row1, row2);
        }

    private:

        EngineType							engine_;

        template<typename ET2>
        requires
            std::default_initializable<ET2>
            and
            std::copyable<ET2>
            and
            matrix_engine<ET2>
        friend class Matrix;

        /// This constructor allows to create submatrix views and transpose matrix views
        /// It uses tag dispatch
        template<typename ET2, typename ... ARGS>
        constexpr Matrix(detail::special_ctor_tag, ET2&& eng, ARGS&&... args)
        : engine_(std::forward<ET2>(eng), std::forward<ARGS>(args)...) {}

    };     // class Matrix




    // -------------- Matrix Aliases -----------------------------------------------------------

    template<typename T, size_t R, size_t C>
    using Mat = Matrix<
                        MatrixEngine<T,
                                    R, C,
                                    matrix_layout::row_major>
                        >;

    template <typename T>
    using Mat22 = Mat<T, 2, 2>;

    template <typename T>
    using Mat33 = Mat<T, 3, 3>;

    template <typename T>
    using Mat44 = Mat<T, 4, 4>;

    // float precision
    using Mat2f = Mat<float, 2, 2>;
    using Mat3f = Mat<float, 3, 3>;
    using Mat4f = Mat<float, 4, 4>;

    // double precision
    using Mat2d = Mat<double, 2, 2>;
    using Mat3d = Mat<double, 3, 3>;
    using Mat4d = Mat<double, 4, 4>;




//
//    template<class T, size_t R, class COT = void>
//    using fixed_size_column_vector =
//            matrix<matrix_storage_engine<T, R, 1, void, matrix_layout::column_major>, COT>;
//
//    template<class T, size_t C, class COT = void>
//    using fixed_size_row_vector =
//            matrix<matrix_storage_engine<T, 1, C, void, matrix_layout::row_major>, COT>;
//
//
//    template<class T, size_t R, size_t C, class A = std::allocator<T>, class COT = void>
//    using general_matrix =
//            matrix<matrix_storage_engine<T, R, C, A, matrix_layout::row_major>, COT>;


    // -------------- Equality Comparison ------------------------------------------------------

    template <typename ET1, typename ET2>
    constexpr bool operator==(Matrix<ET1> const& lhs, Matrix<ET2> const& rhs)
    {
    	return support::are_engines_equal(lhs.engine(), rhs.engine());
    }

    template <typename ET1, typename ET2>
    constexpr bool operator!=(Matrix<ET1> const& lhs, Matrix<ET2> const& rhs)
    {
    	return !support::are_engines_equal(lhs.engine(), rhs.engine());
    }


} // namespace pgeo

#endif //PGEOCL_MATRIX_H
