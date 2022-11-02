#ifndef PGEOCL_MATRIX_H
#define PGEOCL_MATRIX_H

#include <pgeo.h>

namespace pgeo {

    template <typename EngineType>
    class Matrix {

    public:
        using element_type              = typename EngineType::element_type;
        using value_type                = typename EngineType::value_type;
        using reference                 = typename EngineType::reference;
        using const_reference           = typename EngineType::const_reference;
        using difference_type           = typename EngineType::difference_type;
        using index_type                = typename EngineType::index_type;
        using index_tuple               = typename EngineType::index_tuple;
        using transpose_type			= Matrix&;
        using const_transpose_type		= Matrix const&;
        using span_type					= typename EngineType::span_type;
        using const_span_type			= typename EngineType::const_span_type;


        // destructor
        ~Matrix() = default;

        // default constructor
        constexpr Matrix() = default;

        // move constructor
        constexpr Matrix(Matrix&&) noexcept = default;

        // Copy constructor
        constexpr Matrix(Matrix const&) = default;

        // constructor with same engine but different type and size
        template <typename EngineType2>
        constexpr Matrix(Matrix<EngineType2> const& src);

        // constructor with initialization list (without type conversion)
        template<typename T2>
        constexpr Matrix(std::initializer_list<std::initializer_list<T2>> listOfRows);

        // move assignment
        constexpr Matrix& operator=(Matrix&&) noexcept = default;

        // copy assignment
        constexpr Matrix& operator=(Matrix const&) = default;

        // Assignment with same engine but different type and size
        template <typename EngineType2>
        constexpr Matrix& operator=(Matrix<EngineType2> const& rhs);

        // Assignment with initialization list (with type conversion)
        template<typename T2>
        constexpr Matrix& operator=(std::initializer_list<std::initializer_list<T2>> listOfRows);

        // ------------------  Capacity --------------------------------

        constexpr index_type columns() const noexcept;
        constexpr index_type rows() const noexcept;
        constexpr index_tuple size() const noexcept;

        // ------------------  Element access --------------------------

        constexpr reference			operator()(index_type i, index_type j);
        constexpr const_reference	operator()(index_type i, index_type j) const;

        constexpr transpose_type			t();
        constexpr const_transpose_type		t() const;

        // ------------------  Data access ----------------------------

        constexpr EngineType&			engine() noexcept;
        constexpr EngineType const&	engine() const noexcept;

        constexpr span_type			span() noexcept;
        constexpr const_span_type	span() const noexcept;

        // ------------------  Modifiers ------------------------------

        constexpr void swap(Matrix& rhs) noexcept;
        constexpr void swapColumns(index_type col1, index_type col2) noexcept;
        constexpr void swapRows(index_type row1, index_type row2) noexcept;

    private:

        EngineType							engine_;

        template<typename ET2> friend class Matrix;
        template<typename ET2> friend class vector;

    };     // class Matrix

    // ------------ Constructor implementations -----------------------------------------

    template <typename EngineType1>
    template <typename EngineType2>
    constexpr Matrix<EngineType1>::Matrix(Matrix<EngineType2> const& src)
        : engine_(src.engine_) { }

    template<typename ET>
    template <typename T>
    constexpr Matrix<ET>::Matrix(std::initializer_list<std::initializer_list<T>> listOfRows)
        : engine_(listOfRows) {}

    template<typename EngineType>
    template<typename EngineType2>
    constexpr Matrix<EngineType>& Matrix<EngineType>::operator=(Matrix<EngineType2> const& rhs)
    {
        engine_ = rhs.engine_;
        return *this;
    }

    template<typename EngineType>
    template<typename T>
    constexpr Matrix<EngineType>& Matrix<EngineType>::operator=(std::initializer_list<std::initializer_list<T>> listOfRows)
    {
        engine_ = listOfRows;
        return *this;
    }

    // ----------------- Size Implementation -----------------------------------------

    template<typename EngineType>
    constexpr auto Matrix<EngineType>::columns() const noexcept -> index_type {
        return engine_.columns();
    }

    template<typename EngineType>
    constexpr auto Matrix<EngineType>::rows() const noexcept -> index_type {
        return engine_.rows();
    }

    template<typename EngineType>
    constexpr auto Matrix<EngineType>::size() const noexcept -> index_tuple {
        return index_tuple(engine_.rows(),engine_.columns());
    }

    // --------- Element Access Implementation ------------------------------------------

    template<typename EngineType>
    constexpr auto Matrix<EngineType>::operator()(index_type i, index_type j) -> reference {
        return engine_(i,j);
    }

    template<typename EngineType>
    constexpr auto Matrix<EngineType>::operator()(index_type i, index_type j) const -> const_reference {
        return engine_(i,j);
    }

    // TODO: refactor this
    template<typename EngineType>
    constexpr auto Matrix<EngineType>::t() -> Matrix &{
        return engine_.t();
    }

    // TODO: refactor this
    template<typename EngineType>
    constexpr auto Matrix<EngineType>::t() const -> const Matrix& {
        return engine_.t();
    }

    // ------------ Data Access Implementation --------------------------------------------
    template<typename EngineType>
    constexpr auto Matrix<EngineType>::engine() noexcept -> EngineType& {
        return engine_;
    }

    template<typename EngineType>
    constexpr auto Matrix<EngineType>::engine() const noexcept -> const EngineType & {
        return engine_;
    }

    template<typename EngineType>
    constexpr auto Matrix<EngineType>::span() noexcept -> span_type {
        return engine_.span();
    }

    template<typename EngineType>
    constexpr auto Matrix<EngineType>::span() const noexcept -> const_span_type {
        return engine_.span();
    }

    // ----------------------- Modifiers Implementation ------------------------------

    template<typename ET>
    constexpr void Matrix<ET>::swap(Matrix& rhs) noexcept
    {
        engine_.swap(rhs);
    }

    template<typename EngineType>
    constexpr void Matrix<EngineType>::swapColumns(index_type col1, index_type col2) noexcept
    {
        engine_.swapColumns(col1,col2);
    }

    template<typename EngineType>
    constexpr void Matrix<EngineType>::swapRows(index_type row1, index_type row2) noexcept
    {
        engine_.swapRows(row1,row2);
    }

    // -------------- Equality Comparison ------------------------------------------------------

    template <typename ET1, typename ET2>
    constexpr bool operator==(Matrix<ET1> const& lhs, Matrix<ET2> const& rhs)
    {
    	return detail::matrixComparisonEquality(lhs.engine(), rhs.engine());
    }

    template <typename ET1, typename ET2>
    constexpr bool operator!=(Matrix<ET1> const& lhs, Matrix<ET2> const& rhs)
    {
    	return !detail::matrixComparisonEquality(lhs.engine(), rhs.engine());
    }


} // namespace pgeo

#endif //PGEOCL_MATRIX_H
