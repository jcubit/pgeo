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

        // evaluates to EngineType if it's an owning engine.
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
        constexpr Matrix(const Matrix &) = default;

        /// constructor from different engine, but constructible from
        /// the current engine
        template <typename EngineType2>
        constexpr Matrix(const Matrix<EngineType2> & src)
        requires
            mutable_matrix_engine<EngineType>
            and
            std::constructible_from<EngineType, EngineType2>
        : engine_(src.engine_) {}

        /// Constructor from different engine and not constructible from
        /// the current engine
        template <typename EngineType2>
        constexpr Matrix(const Matrix<EngineType2> & src)
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

        // (Co-)Vector constructors from std::array or std::vector
        template<typename Container>
        constexpr explicit Matrix(const Container& src)
        requires
            mutable_vector_or_covector_engine<EngineType>
            and
            support::is_std_array_or_vector_v<Container>
            and
            std::constructible_from<EngineType, Container>
        :   engine_(src)
        {}

        template<typename Container>
        constexpr explicit Matrix(const Container & src)
        requires
            mutable_vector_or_covector_engine<EngineType>
            and
            support::is_std_array_or_vector_v<Container>
            and
            (not std::constructible_from<EngineType, Container>)
            and
            std::convertible_to<typename Container::value_type, typename EngineType::element_type>
        :   engine_()
        {
                support::assign_from(engine_, src);
        }

        // Constructor of (co-)vector from initialization list
        template<typename U>
        constexpr Matrix(std::initializer_list<U> src)
        requires
            mutable_vector_or_covector_engine<EngineType>
            and
            std::constructible_from<EngineType, decltype(src)>
        :   engine_(src)
        {}

        template<typename U>
        constexpr Matrix(std::initializer_list<U> src)
        requires
            mutable_vector_or_covector_engine<EngineType>
            and
            (not std::constructible_from<EngineType, decltype(src)>)
            and
            std::convertible_to<U, element_type>
        :   engine_()
        {
                support::assign_from(engine_, src);
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

        // Assignment with 2D initialization list (with type conversion)
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

        // Assignment with 2D initialization list (with type conversion) when engine is not assignable
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

        // Assignment with std::array or std::vector (with type conversion)
        template<typename Container>
        constexpr Matrix& operator =(Container const& rhs)
        requires
        mutable_vector_or_covector_engine<EngineType>
        and
        support::is_std_array_or_vector_v<Container>
        and
        std::assignable_from<EngineType, decltype(rhs)>
        {
            engine_ = rhs;
            return *this;
        }

        template<typename Container>
        constexpr Matrix&
        operator =(Container const& rhs)
        requires
            mutable_vector_or_covector_engine<EngineType>
            and
            support::is_std_array_or_vector_v<Container>
            and
            (not std::assignable_from<EngineType, decltype(rhs)>)
            and
            std::convertible_to<typename Container::value_type, element_type>
        {
            support::assign_from(engine_, rhs);
            return *this;
        }

        // Assignment with 1D initialization list (with type conversion)
        template<typename U>
        constexpr Matrix& operator =(std::initializer_list<U> rhs)
            requires
            mutable_vector_or_covector_engine<EngineType>
            and
            std::assignable_from<EngineType, decltype(rhs)>
        {
            engine_ = rhs;
            return *this;
        }

        template<typename U>
        constexpr Matrix&
        operator =(std::initializer_list<U> rhs)
        requires
            mutable_vector_or_covector_engine<EngineType>
            and
            (not std::assignable_from<EngineType, decltype(rhs)>)
            and
            std::convertible_to<U, element_type>
        {
            support::assign_from(engine_, rhs);
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

        constexpr reference operator ()(size_type i)
        requires
            mutable_vector_or_covector_engine<EngineType>
        {
            return engine_(i);
        }

        constexpr const_reference operator ()(size_type i) const
        requires
            mutable_vector_or_covector_engine<EngineType>
        {
            return engine_(i);
        }


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

        constexpr span_type			span() noexcept
        requires support::is_owning_engine_type_v<EngineType>
        {
            return engine_.span();
        }
        constexpr const_span_type	span() const noexcept
        requires support::is_owning_engine_type_v<EngineType>
        {
            return engine_.span();
        }

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

        /// This constructor allows to create submatrix views and transpose matrix views via tag dispatch
        template<typename ET2, typename ... ARGS>
        constexpr Matrix(detail::special_ctor_tag, ET2&& eng, ARGS&&... args)
        : engine_(std::forward<ET2>(eng), std::forward<ARGS>(args)...) {}

    };     // class Matrix




    // -------------- Matrix Aliases -----------------------------------------------------------

    template<typename T, size_t R, size_t C, typename L = matrix_layout::row_major>
    using Mat = Matrix<
                        MatrixEngine<T,
                                    R, C,
                                    L>
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

    // Vectors are assumed to be column vectors in Pgeo
    template<typename T, size_t R>
    using Vec = Matrix<
            MatrixEngine<T,
                    R, 1,
                    matrix_layout::column_major>>;

    using Vec2i = Vec<int,2>;
    using Vec3i = Vec<int,3>;
    using Vec4i = Vec<int,4>;

    using Vec2f = Vec<float,2>;
    using Vec3f = Vec<float,3>;
    using Vec4f = Vec<float,4>;

    using Vec2d = Vec<double,2>;
    using Vec3d = Vec<double,3>;
    using Vec4d = Vec<double,4>;

    // Co-vectors are assumed to be row vectors in Pgeo
    template<typename T, size_t C>
    using CoVec = Matrix<
            MatrixEngine<T,
                    1, C,
                    matrix_layout::row_major>>;

    using CoVec2i = CoVec<int,2>;
    using CoVec3i = CoVec<int,3>;
    using CoVec4i = CoVec<int,4>;

    using CoVec2f = CoVec<float,2>;
    using CoVec3f = CoVec<float,3>;
    using CoVec4f = CoVec<float,4>;

    using CoVec2d = CoVec<double,2>;
    using CoVec3d = CoVec<double,3>;
    using CoVec4d = CoVec<double,4>;


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
