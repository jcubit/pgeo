#ifndef PGEOCL_TRANSPOSEVIEWENGINE_H
#define PGEOCL_TRANSPOSEVIEWENGINE_H

#include <pgeo.h>

namespace pgeo
{

    template<class EngineType>
    class TransposeViewEngine
    {
    public:
        using element_type    = typename EngineType::element_type;
        using value_type      = typename EngineType::value_type;
        using pointer         = typename EngineType::pointer;
        using const_pointer   = typename EngineType::const_pointer;
        using reference       = typename EngineType::refence;
        using const_reference = typename EngineType::const_reference;
        using difference_type = typename EngineType::difference_type;
        using index_type      = typename EngineType::index_type;
        using index_tuple     = typename EngineType::index_tuple;
        using span_type       = typename EngineType::span_type;
        using const_span_type = typename EngineType::const_span_type;

        // destructor
        ~TransposeViewEngine() noexcept = default;

        // default constructor
        constexpr TransposeViewEngine();
        // Move constructors
        constexpr TransposeViewEngine(TransposeViewEngine&&) noexcept = default;
        // Copy constructor
        constexpr TransposeViewEngine(TransposeViewEngine const&) noexcept = default;
        // Move assignment
        constexpr TransposeViewEngine&     operator =(TransposeViewEngine&&) noexcept = default;
        // Copy assignment
        constexpr TransposeViewEngine&     operator =(TransposeViewEngine const&) noexcept = default;

        template<typename EngineType2>
        constexpr TransposeViewEngine&     operator =(EngineType2 const& rhs);

        // constructor with initialization list (with type conversion)
        template<typename U>
        constexpr TransposeViewEngine& operator =(std::initializer_list<std::initializer_list<U>> rhs);

        // ------------------  Capacity --------------------------------
        constexpr index_type    columns() const noexcept;
        constexpr index_type    rows() const noexcept;
        constexpr index_tuple   size() const noexcept;

        // ------------------  Element access --------------------------------
        constexpr reference     operator ()(index_type i, index_type j) const;

        // ------------------  Data access --------------------------------
        constexpr span_type     span() const noexcept;

        // ------------------  Modifiers  --------------------------------
        constexpr void          swap(TransposeViewEngine& rhs) noexcept;

    private:
        template<class ET2>  friend class Matrix;

        EngineType *    pReferentEngine_;

        constexpr TransposeViewEngine(EngineType& engine);


    }; // class TransposeViewEngine

    // ------------ Public Constructor and assignment implementations -----------------------------------------
    template<typename ET>
    constexpr TransposeViewEngine<ET>::TransposeViewEngine()
            :   pReferentEngine_(nullptr)
    {}

    template<class EngineType>
    template<class EngineType2>
    constexpr auto TransposeViewEngine<EngineType>::operator =(EngineType2 const& rhs) -> TransposeViewEngine<EngineType> &
    {
        detail::check_source_engine_size(rhs, rows(), columns());
        detail::assign_from_matrix_engine(*this, rhs);
        return *this;
    }

    template<class EngineType>
    template<class U>
    constexpr auto TransposeViewEngine<EngineType>::operator =(std::initializer_list<std::initializer_list<U>> rhs)
    -> TransposeViewEngine<EngineType>&
    {
        detail::check_source_init_list(rhs, rows(), columns());
        detail::assign_from_matrix_initlist(*this, rhs);
        return *this;
    }

    // ------------ Private Constructor -----------------------------------------
    template<class EngineType>
    constexpr TransposeViewEngine<EngineType>::TransposeViewEngine(EngineType& engine)
            : pReferentEngine_(&engine)
    {}

    // -------- Size queries Implementation ---------------------------------------------------------
    template<class EngineType>
    constexpr auto TransposeViewEngine<EngineType>::columns() const noexcept -> index_type
    {
        return pReferentEngine_->rows();

    }

    template<class EngineType>
    constexpr auto TransposeViewEngine<EngineType>::rows() const noexcept -> index_type
    {
        return pReferentEngine_->columns();
    }

    template<class EngineType>
    constexpr auto TransposeViewEngine<EngineType>::size() const noexcept -> index_tuple
    {
        return index_tuple(pReferentEngine_->columns(), pReferentEngine_->rows());
    }



    // -------- Element Access Implementation ------------------------------------------------------
    template<class EngineType>
    constexpr auto TransposeViewEngine<EngineType>::operator ()(index_type i, index_type j) const -> reference
    {
        return (*pReferentEngine_)(j, i);
    }

    // -------- Data Access Implementation ------------------------------------------------------
    template<class EngineType>
    constexpr auto TransposeViewEngine<EngineType>::span() const noexcept -> span_type
    {
        // TODO: Clean this
//        dyn_mat_extents     ext(s.extent(1), s.extent(0));
//        dyn_mat_strides     str{s.stride(1), s.stride(0)};
//        dyn_mat_mapping     map(ext, str);
//        return noe_mdspan_transpose_t<ST>(s.data(), map);
//
//        using dyn_mat_extents = extents<dynamic_extent, dynamic_extent>;
//        using dyn_mat_strides = array<typename dyn_mat_extents::index_type, 2>;
//        using dyn_mat_layout  = layout_stride<dynamic_extent, dynamic_extent>;
//        using dyn_mat_mapping = typename dyn_mat_layout::template mapping<dyn_mat_extents>;
        // --

        const_span_type span = pReferentEngine_->span();

        using matrix_extent = stdex::extents<span.extent(1), span.extent(0)>;
        using matrix_layout = stdex::layout_stride<span.extent(1), span.extent(0)>;
        using matrix_mapping = typename matrix_layout::template mapping<matrix_extent>;

        std::array<index_type , 2>    strides{span.stride(1), span.stride(0)};
        matrix_extent extent;
        matrix_mapping mapping(extent, strides);

        return stdex::mdspan<span_type>(span.data(), mapping);
    }

    // -------- Modifiers Access Implementation ------------------------------------------------------
    template<class EngineType>
    constexpr void TransposeViewEngine<EngineType>::swap(TransposeViewEngine& rhs) noexcept
    {
        if (&rhs != this)
        {
            std::swap(pReferentEngine_, rhs.p_referentEngine_);
        }
    }

}

#endif //PGEOCL_TRANSPOSEVIEWENGINE_H
