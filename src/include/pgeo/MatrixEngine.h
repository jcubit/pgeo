#ifndef PGEOCL_MATRIXENGINE_H
#define PGEOCL_MATRIXENGINE_H

#include <pgeo.h>


namespace pgeo {

    template<class T, ptrdiff_t R, ptrdiff_t C>
    class MatrixEngine
    {
        static_assert(R >= 1, "Number of rows must at least 1" );
        static_assert(C >= 1, "Number of columns must at least 1");

    public:

        //using engine_category = initable_matrix_engine_tag;
        using element_type    = T;
        using value_type      = std::remove_cv_t<T>;
        using pointer         = element_type*;
        using const_pointer   = element_type const*;
        using reference       = element_type&;
        using const_reference = element_type const&;
        using difference_type = ptrdiff_t;
        using index_type      = ptrdiff_t;
        using index_tuple     = stdex::extents<R, C>;
        using span_type       = stdex::mdspan<element_type, R, C>;
        using const_span_type = stdex::mdspan<element_type const, R, C>;


        // destructor
        ~MatrixEngine() noexcept = default;

        // default constructor
        constexpr MatrixEngine();

        // Move constructors
        constexpr MatrixEngine(MatrixEngine&&) noexcept = default;

        // Copy constructor
        constexpr MatrixEngine(MatrixEngine const&) noexcept = default;

        // constructor with same engine but different type and size
        template <typename T2, ptrdiff_t R2, ptrdiff_t C2>
        constexpr MatrixEngine(MatrixEngine<T2, R2, C2> const& src);

        // constructor from totally different engine type
        template <typename ET2>
        constexpr MatrixEngine(ET2 const& src);

        // constructor with initialization list (with type conversion)
        template<typename T2>
        constexpr MatrixEngine(std::initializer_list<std::initializer_list<T2>> rhs);


        // move assignment
        constexpr MatrixEngine& operator=(MatrixEngine&&) noexcept = default;

        // copy assignment
        constexpr MatrixEngine& operator=(MatrixEngine const&) = default;

        // Assignment with same engine but different type and size
        template <typename T2, ptrdiff_t R2, ptrdiff_t C2>
        constexpr MatrixEngine& operator=(MatrixEngine<T2, R2, C2> const& rhs);

        // Assignment from totally different engine type
        template <typename ET2>
        constexpr MatrixEngine& operator=(ET2 const& rhs);

        // Assignment with initialization list (with type conversion)
        template<typename T2>
        constexpr MatrixEngine& operator=(std::initializer_list<std::initializer_list<T2>> rhs);

        // ------------------  Capacity --------------------------------

        constexpr index_type columns() const noexcept;
        constexpr index_type rows() const noexcept;
        constexpr index_tuple size() const noexcept;

        // ------------------  Element access --------------------------

        constexpr reference			operator()(index_type i, index_type j);
        constexpr const_reference	operator()(index_type i, index_type j) const;

        // ------------------  Data access --------------------------
        constexpr span_type			span() noexcept;
        constexpr const_span_type	span() const noexcept;

        // ------------------  Modifiers  --------------------------
        constexpr void swap(MatrixEngine& rhs) noexcept;
        constexpr void swapColumns(index_type j1, index_type j2) noexcept;
        constexpr void swapRows(index_type i1, index_type i2) noexcept;

    private:

        template<typename T2, ptrdiff_t R2, ptrdiff_t C2> friend class MatrixEngine;

        /// The element entries of the matrix
        std::array<T, R*C>							matrixElements_;

        template<typename T2, ptrdiff_t R2, ptrdiff_t C2>
        constexpr void assign(MatrixEngine<T2, R2, C2> const& rhs);

        template <typename ET2>
        constexpr void assign(ET2 const& rhs);

        template <typename T2>
        constexpr void assign(std::initializer_list<std::initializer_list<T2>> rhs);

    };     // class MatrixEngine


    // ------------ Constructor implementations -----------------------------------------

    template<class T, ptrdiff_t R, ptrdiff_t C>
    constexpr MatrixEngine<T, R, C>::MatrixEngine()
            : matrixElements_() { }

    template<typename T, ptrdiff_t R, ptrdiff_t C>
    template <typename T2, ptrdiff_t R2, ptrdiff_t C2>
    constexpr MatrixEngine<T, R, C>::MatrixEngine(MatrixEngine<T2, R2, C2> const& src)
            : matrixElements_()
    {
        assign(src);
    }

    template <typename T, ptrdiff_t R, ptrdiff_t C>
    template <typename ET2>
    constexpr MatrixEngine<T, R, C>::MatrixEngine(ET2 const& src)
            : matrixElements_()
    {
        assign(src);
    }

    template <typename T, ptrdiff_t R, ptrdiff_t C>
    template<typename T2>
    constexpr MatrixEngine<T, R, C>::MatrixEngine(std::initializer_list<std::initializer_list<T2>> rhs)
            : matrixElements_()
    {
        assign(rhs);
    }

    // ----------------- Public Assignment --------------------------------------


    template <typename T, ptrdiff_t R, ptrdiff_t C>
    template <typename T2, ptrdiff_t R2, ptrdiff_t C2>
    constexpr MatrixEngine<T,R,C>& MatrixEngine<T, R, C>::operator=(MatrixEngine<T2, R2, C2> const& rhs)
    {
        assign(rhs);
        return *this;
    }

    template <typename T, ptrdiff_t R, ptrdiff_t C>
    template <typename ET2>
    constexpr MatrixEngine<T, R, C>& MatrixEngine<T, R, C>::operator=(ET2 const& rhs)
    {
        assign(rhs);
        return *this;
    }

    template <typename T, ptrdiff_t R, ptrdiff_t C>
    template<typename T2>
    constexpr MatrixEngine<T, R, C>& MatrixEngine<T, R, C>::operator=(std::initializer_list<std::initializer_list<T2>> rhs)
    {
        assign(rhs);
        return *this;
    }

    // ------- Private Assign Implementations --------------------------------------------

    template<typename T, ptrdiff_t R, ptrdiff_t C>
    template<typename T2, ptrdiff_t R2, ptrdiff_t C2>
    constexpr void MatrixEngine<T, R, C>::assign(MatrixEngine<T2, R2, C2> const& rhs)
    {
        static_assert(R == R2 && C == C2,
                      "Size of matrix does not coincide in private assign member method");

        for (index_type i = 0; i < (R * C); ++i) {
            matrixElements_[i] = static_cast<T>(rhs.matrixElements_[i]);
        }
    }

    template<typename T, ptrdiff_t R, ptrdiff_t C>
    template<typename ET2>
    constexpr void MatrixEngine<T, R, C>::assign(ET2 const& rhs)
    {
        // TODO: replace assertions with a Matrix Engine Concept.
        //static_assert(is_matrix_engine_v<ET2>);
        detail::check_source_engine_size(rhs, R, C);
        detail::assign_from_matrix_engine(*this, rhs);
    }

    template <typename T, ptrdiff_t R, ptrdiff_t C>
    template <typename T2>
    constexpr void MatrixEngine<T, R, C>::assign(std::initializer_list<std::initializer_list<T2>> rhs)
    {
        detail::check_source_init_list(rhs, R, C);
        detail::assign_from_matrix_initlist(*this, rhs);
    }

    // -------- Size queries Implementation ---------------------------------------------------------

    template <typename T, ptrdiff_t R, ptrdiff_t C>
    constexpr auto MatrixEngine<T, R, C>::columns() const noexcept -> index_type
    {
        return C;
    }

    template <typename T, ptrdiff_t R, ptrdiff_t C>
    constexpr auto MatrixEngine<T, R, C>::rows() const noexcept -> index_type
    {
        return R;
    }

    template<typename T, ptrdiff_t R, ptrdiff_t C>
    constexpr auto MatrixEngine<T, R, C>::size() const noexcept -> index_tuple
    {
        return index_tuple{}; // TODO
    }

    // -------- Element Access Implementation ------------------------------------------------------

    template<typename T, ptrdiff_t R, ptrdiff_t C>
    constexpr auto MatrixEngine< T, R, C>::operator()(index_type i, index_type j) -> reference
    {
        return matrixElements_[i * C + j];
    }

    template<typename T, ptrdiff_t R, ptrdiff_t C>
    constexpr auto MatrixEngine< T, R, C>::operator()(index_type i, index_type j) const -> const_reference
    {
        return matrixElements_[i * C + j];
    }

    // -------- Data Access Implementation ------------------------------------------------------

    template<typename T, ptrdiff_t R, ptrdiff_t C>
    constexpr auto MatrixEngine<T, R, C>::span() noexcept -> span_type
    {
        return span_type(matrixElements_.data());
    }

    template<typename T, ptrdiff_t R, ptrdiff_t C>
    constexpr auto MatrixEngine<T, R, C>::span() const noexcept -> const_span_type
    {
        return const_span_type(matrixElements_.data());
    }

    // --------- Public Modifiers ---------------------------------------------------------------

    template<typename T, ptrdiff_t R, ptrdiff_t C>
    constexpr void MatrixEngine<T, R, C>::swap(MatrixEngine& rhs) noexcept
    {
        if (&rhs != this) {
            std::swap(matrixElements_, rhs.data_);
        }
    }

    template<typename T, ptrdiff_t R, ptrdiff_t C>
    constexpr void MatrixEngine<T, R, C>::swapColumns(index_type j1, index_type j2) noexcept
    {
        if (j1 != j2) {
            for (index_type i = 0; i < R; ++i) {
                std::swap(matrixElements_[i*C + j1], matrixElements_[i * C + j2]);
            }
        }
    }

    template<typename T, ptrdiff_t R, ptrdiff_t C>
    constexpr void MatrixEngine<T, R, C>::swapRows(index_type i1, index_type i2) noexcept
    {
        if (i1 != i2) {
            for (index_type j = 0; j < C; ++j) {
                std::swap(matrixElements_[i1 * C + j], matrixElements_[i2 * C + j]);
            }
        }
    }

}


#endif //PGEOCL_MATRIXENGINE_H
