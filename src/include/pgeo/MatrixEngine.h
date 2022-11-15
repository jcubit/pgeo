#ifndef PGEOCL_MATRIXENGINE_H
#define PGEOCL_MATRIXENGINE_H

#include <pgeo.h>


namespace pgeo {

    /// Default RAII Engine Type for fixed size matrices that owns memory through std::array
    /// It also handles how the access of the elements is depending on the layout
    template<typename T, size_t R, size_t C, typename L>
    requires
        valid_fixed_engine_size<R,C>
        and
        valid_layout_for_storage_engine<L>
        and
        valid_matrix_elements<T>
    class MatrixEngine
    {

    public:

        /// The element entries of the matrix
        std::array<T, R*C>							matrixElements_;

        static constexpr bool   is_column_matrix        = (C == 1);
        static constexpr bool   is_row_matrix           = (R == 1);
        static constexpr bool   is_vector_or_covector   = (is_column_matrix || is_row_matrix);
        static constexpr bool   is_column_major         = std::is_same_v<L, matrix_layout::column_major>;
        static constexpr bool   is_row_major            = std::is_same_v<L, matrix_layout::row_major>;

        static constexpr size_t     rows_   = R;
        static constexpr size_t     cols_   = C;

        using element_type    = T;
        using layout_type     = L;
        using reference       = element_type&;
        using const_reference = element_type const&;
        using size_type       = size_t;
        using span_type       = stdex::mdspan<element_type, R, C>;
        using const_span_type = stdex::mdspan<element_type const, R, C>;



        // destructor
        ~MatrixEngine() noexcept = default;

        // default constructor
        constexpr MatrixEngine() = default;
        // Move constructors
        constexpr MatrixEngine(MatrixEngine&&) noexcept = default;
        // Copy constructor
        constexpr MatrixEngine(MatrixEngine const&) noexcept = default;

        // constructor from different engine type
        template <typename ET2>
        constexpr MatrixEngine(ET2 const& src)
            requires
            matrix_engine<ET2>
            and
            std::convertible_to<typename ET2::element_type, element_type>
        : matrixElements_()
        {
          support::assign_from(*this, src);
        }

        // constructor with initialization list (with type conversion)
        template<typename T2>
        constexpr MatrixEngine(std::initializer_list<std::initializer_list<T2>> src)
        requires std::convertible_to<T2, T>
        : matrixElements_()
        {
            support::assign_from(*this, src);
        }

        // Vector and covector constructors
        template<typename Container>
        constexpr MatrixEngine(const Container& src)
        requires
            is_vector_or_covector
            and
            support::is_std_array_or_vector_v<Container>
            and
            std::convertible_to<typename Container::value_type, element_type>
        : matrixElements_()
        {
            support::assign_from(*this, src);
        }

        template<typename U>
        constexpr MatrixEngine(std::initializer_list<U> src)
        requires
            is_vector_or_covector
            and
            std::convertible_to<U, element_type>
        :   matrixElements_()
        {
            support::assign_from(*this, src);
        }


        // move assignment
        constexpr MatrixEngine& operator=(MatrixEngine&&) noexcept = default;

        // copy assignment
        constexpr MatrixEngine& operator=(MatrixEngine const&) = default;

        // Assignment from different engine type.
        // It performs type conversion
        template <typename ET2>
        constexpr MatrixEngine& operator=(ET2 const& rhs)
        requires
        matrix_engine<ET2>
        and
        std::convertible_to<typename ET2::element_type, element_type>
        {
            support::assign_from(*this, rhs);
            return *this;
        }

        // Assignment with initialization list (with type conversion)
        template<typename U>
        constexpr MatrixEngine& operator=(std::initializer_list<std::initializer_list<U>> rhs)
                requires std::convertible_to<U, element_type>
        {
            support::assign_from(*this, rhs);
            return *this;
        }

        // (Co-)vector assignment
        template<typename Container>
        constexpr MatrixEngine& operator=(Container const& rhs)
        requires
        is_vector_or_covector
        and
        support::is_std_array_or_vector_v<Container>
        and
        std::convertible_to<typename Container::value_type, element_type>
        {
            support::assign_from(*this, rhs);
            return *this;
        }

        template<class U>
        constexpr MatrixEngine& operator =(std::initializer_list<U> rhs)
        requires
        is_vector_or_covector
        and
        std::convertible_to<U, element_type>
        {
            support::assign_from(*this, rhs);
            return *this;
        }

        // ------------------  Size --------------------------------

        constexpr size_type columns() const noexcept
        {
            return cols_;
        }
        constexpr size_type rows() const noexcept
        {
            return rows_;
        }
        constexpr std::tuple<size_type,size_type> size() const noexcept
        {
            return std::make_tuple(rows_,cols_);
        }

        // ------------------  Element access --------------------------

        constexpr reference			operator()(size_type i, size_type j)
        requires is_row_major
        {
            return matrixElements_[i*cols_ + j];
        }

        constexpr reference			operator()(size_type i, size_type j)
        requires is_column_major
        {
            return matrixElements_[j*rows_ + i];
        }


        constexpr const_reference	operator()(size_type i, size_type j) const
        requires is_row_major
        {
            return matrixElements_[i*cols_ + j];
        }

        constexpr const_reference	operator()(size_type i, size_type j) const
        requires is_column_major
        {
            return matrixElements_[j*rows_ + i];
        }

        // ------------------ (Co-)Vector Element access --------------------------

        constexpr reference operator ()(size_type i)
        requires
        is_vector_or_covector
        {
            return matrixElements_[i];
        }

        constexpr const_reference operator ()(size_type i) const
        requires
        is_vector_or_covector
        {
            return matrixElements_[i];
        }

        // ------------------  Data access --------------------------
        constexpr span_type			span() noexcept
        {
            return span_type(matrixElements_.data());
        }
        constexpr const_span_type	span() const noexcept
        {
            return const_span_type(matrixElements_.data());
        }

        // ------------------  Modifiers  --------------------------
        constexpr void swap(MatrixEngine& rhs) noexcept
        {
            std::swap(matrixElements_, rhs.matrixElements_);
        }
        constexpr void swapColumns(size_type j1, size_type j2) noexcept
        requires is_row_major
        {
            if (j1 != j2) {
                for (size_type i = 0; i < rows_; ++i) {
                    std::swap(matrixElements_[i*cols_ + j1], matrixElements_[i * cols_ + j2]);
                }
            }
        }
        constexpr void swapRows(size_type i1, size_type i2) noexcept
        requires is_row_major
        {
            if (i1 != i2) {
                for (size_type j = 0; j < cols_; ++j) {
                    std::swap(matrixElements_[i1 * cols_ + j], matrixElements_[i2 * cols_ + j]);
                }
            }
        }


    };     // class MatrixEngine

} // namespace pgeo


#endif //PGEOCL_MATRIXENGINE_H
