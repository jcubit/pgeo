#ifndef PGEOCL_MATRIXVIEWENGINE_H
#define PGEOCL_MATRIXVIEWENGINE_H

#include <pgeo.h>

namespace pgeo {

    template<typename EngineType, typename MatrixViewTag>
    class MatrixViewEngine;

    /// Matrix engine that acts as a view and therefore is non-owning
    /// This engine is used for submatrix views
    /// The submatrix definition is the subset
    /// [rowStart_,rowStart_ + rowStep_) x [colStart_, colStart_ + colStep_)
    template<class EngineType>
    requires mutable_matrix_engine<EngineType>
    class MatrixViewEngine<EngineType, matrix_view::submatrix>
    {

        using engine_pointer        = EngineType *;

    public:

        using owning_engine_type    = support::get_owning_engine_type_t<EngineType>;
        using element_type          = typename EngineType::element_type;
        using reference             = typename EngineType::reference;
        using const_reference       = typename EngineType::const_reference;
        using size_type             = typename EngineType::size_type;
        using span_type             = typename EngineType::span_type;
        using const_span_type       = typename EngineType::const_span_type;

        // destructor
        ~MatrixViewEngine() noexcept = default;

        // default constructor
        constexpr MatrixViewEngine() noexcept
        : pReferentEngine_(nullptr)
        , rowStart_(0)
        , rowStep_(0)
        , colStart_(0)
        , colStep_(0)
        {}

        explicit constexpr MatrixViewEngine(EngineType& engine,
                                            size_type rowStart, size_type rowStep,
                                            size_type colStart, size_type colStep) noexcept
        : pReferentEngine_(&engine)
        , rowStart_(rowStart)
        , rowStep_(rowStep)
        , colStart_(colStart)
        , colStep_(colStep)
        {}

        // Move constructors
        constexpr MatrixViewEngine(MatrixViewEngine&&) noexcept = default;
        // Copy constructor
        constexpr MatrixViewEngine(MatrixViewEngine const&) noexcept = default;
        // Move assignment
        constexpr MatrixViewEngine&     operator =(MatrixViewEngine&&) noexcept = default;
        // Copy assignment
        constexpr MatrixViewEngine&     operator =(MatrixViewEngine const&) noexcept = default;

        constexpr bool
        isValid() const noexcept
        {
            return pReferentEngine_ != nullptr;
        }

        // ------------------  Size --------------------------------
        constexpr size_type    columns() const noexcept { return colStep_; }
        constexpr size_type    rows() const noexcept { return rowStep_; }
        constexpr std::tuple<size_type, size_type>  size() const noexcept
        {
            return std::make_tuple(rowStep_, colStep_);
        }

        // ------------------  Element access --------------------------------
        constexpr reference     operator ()(size_type i, size_type j) const
        {
            return (*pReferentEngine_)(rowStart_ + i, colStart_ + j );
        }


        // TODO: Do we need this? consider removing
        // ------------------  Modifiers  --------------------------------
        constexpr void          swap(MatrixViewEngine& rhs) noexcept
        {
            std::swap(*this, rhs);
        }

    private:

        engine_pointer   pReferentEngine_;
        size_type        rowStart_;
        size_type        rowStep_;
        size_type        colStart_;
        size_type        colStep_;


    }; // class MatrixViewEngine<ET, matrix_view::submatrix>


    /// Matrix engine that acts as a view and therefore is non-owning
    /// This engine is used for submatrix views
    /// The submatrix definition is the subset
    /// [rowStart_,rowStart_ + rowStep_) x [colStart_, colStart_ + colStep_)
    template<class EngineType>
    class MatrixViewEngine<EngineType, matrix_view::const_submatrix>
    {

        using engine_pointer  = EngineType const *;

    public:

        using owning_engine_type    = support::get_owning_engine_type_t<EngineType>;
        using element_type          = typename EngineType::element_type;
        using reference             = typename EngineType::const_reference;
        using const_reference       = typename EngineType::const_reference;
        using size_type             = typename EngineType::size_type;
        using span_type             = typename EngineType::const_span_type;
        using const_span_type       = typename EngineType::const_span_type;

        // destructor
        ~MatrixViewEngine() noexcept = default;

        // default constructor
        constexpr MatrixViewEngine() noexcept
                : pReferentEngine_(nullptr)
                , rowStart_()
                , rowStep_()
                , colStart_()
                , colStep_()
        {}

        explicit constexpr MatrixViewEngine(EngineType& engine,
                                            size_type rowStart, size_type rowStep,
                                            size_type colStart, size_type colStep) noexcept
                : pReferentEngine_(&engine)
                , rowStart_(rowStart)
                , rowStep_(rowStep)
                , colStart_(colStart)
                , colStep_(colStep)
        {}

        // Move constructors
        constexpr MatrixViewEngine(MatrixViewEngine&&) noexcept = default;
        // Copy constructor
        constexpr MatrixViewEngine(MatrixViewEngine const&) noexcept = default;
        // Move assignment
        constexpr MatrixViewEngine&     operator =(MatrixViewEngine&&) noexcept = default;
        // Copy assignment
        constexpr MatrixViewEngine&     operator =(MatrixViewEngine const&) noexcept = default;

        constexpr bool
        isValid() const noexcept
        {
            return pReferentEngine_ != nullptr;
        }

        // ------------------  Size --------------------------------
        constexpr size_type    columns() const noexcept { return colStep_; }
        constexpr size_type    rows() const noexcept { return rowStep_; }
        constexpr std::tuple<size_type, size_type>  size() const noexcept
        {
            return std::make_tuple(rowStep_, colStep_);
        }

        // ------------------  Element access --------------------------------
        constexpr reference     operator ()(size_type i, size_type j) const
        {
            return (*pReferentEngine_)(rowStart_ + i, colStart_ + j);
        }

        // TODO: Do we need this? consider removing
        // ------------------  Modifiers  --------------------------------
        constexpr void          swap(MatrixViewEngine& rhs) noexcept
        {
            std::swap(*this, rhs);
        }

    private:

        engine_pointer   pReferentEngine_;
        size_type        rowStart_;
        size_type        rowStep_;
        size_type        colStart_;
        size_type        colStep_;


    }; // class MatrixViewEngine<ET, matrix_view::const_submatrix>


    /// Matrix engine that acts as a view and therefore is non-owning
    /// This engine is used for transpose views
    template<class EngineType>
    requires mutable_matrix_engine<EngineType>
    class MatrixViewEngine<EngineType, matrix_view::transpose>
    {

        using engine_pointer        = EngineType *;
        using mdspan_traits         = support::mdspan_view_traits<support::get_mdspan_type_t<EngineType>>;
        using const_mdspan_traits   = support::mdspan_view_traits<support::get_const_mdspan_type_t<EngineType>>;

    public:

        using owning_engine_type    = support::get_owning_engine_type_t<EngineType>;
        using element_type          = typename EngineType::element_type;
        using layout_type           = support::get_transpose_layout_t<support::get_layout_t<EngineType>>;
        using reference             = typename EngineType::reference;
        using const_reference       = typename EngineType::const_reference;
        using size_type             = typename EngineType::size_type;
        using span_type             = typename mdspan_traits::transpose_mdspan_type;
        using const_span_type       = typename const_mdspan_traits::transpose_mdspan_type;

        // destructor
        ~MatrixViewEngine() noexcept = default;

        // default constructor
        constexpr MatrixViewEngine() noexcept
                : pReferentEngine_(nullptr)
        {}

        explicit constexpr MatrixViewEngine(EngineType& engine) noexcept
                : pReferentEngine_(&engine)
        {}

        // Move constructors
        constexpr MatrixViewEngine(MatrixViewEngine&&) noexcept = default;
        // Copy constructor
        constexpr MatrixViewEngine(MatrixViewEngine const&) noexcept = default;
        // Move assignment
        constexpr MatrixViewEngine&     operator =(MatrixViewEngine&&) noexcept = default;
        // Copy assignment
        constexpr MatrixViewEngine&     operator =(MatrixViewEngine const&) noexcept = default;

        constexpr bool
        isValid() const noexcept
        {
            return pReferentEngine_ != nullptr;
        }

        // ------------------  Size --------------------------------
        constexpr size_type    columns() const noexcept
        requires sizable_engine<EngineType>
        {
            return pReferentEngine_->rows();
        }
        constexpr size_type    rows() const noexcept
        requires sizable_engine<EngineType>
        {
            return pReferentEngine_->columns();
        }
        constexpr std::tuple<size_type, size_type>  size() const noexcept
        requires sizable_engine<EngineType>
        {
            return pReferentEngine_->size();
        }

        // ------------------  Element access --------------------------------
        constexpr reference     operator ()(size_type i, size_type j) const
        {
            return (*pReferentEngine_)(j, i);
        }

        // TODO: Do we need this? consider removing
        // ------------------  Modifiers  --------------------------------
        constexpr void          swap(MatrixViewEngine& rhs) noexcept
        {
            std::swap(pReferentEngine_, rhs.pReferentEngine_);
        }

    private:

        engine_pointer   pReferentEngine_;


    }; // class MatrixViewEngine<ET, matrix_view::transpose>



    /// Matrix engine that acts as a view and therefore is non-owning
    /// This engine is used for const transpose views
    template<class EngineType>
    class MatrixViewEngine<EngineType, matrix_view::const_transpose>
    {

        using engine_pointer  = EngineType *;
        using const_mdspan_traits   = support::mdspan_view_traits<support::get_const_mdspan_type_t<EngineType>>;

    public:

        using owning_engine_type    = support::get_owning_engine_type_t<EngineType>;
        using element_type          = typename EngineType::element_type;
        using layout_type           = support::get_transpose_layout_t<support::get_layout_t<EngineType>>;
        using reference             = typename EngineType::const_reference;
        using const_reference       = typename EngineType::const_reference;
        using size_type             = typename EngineType::size_type;
        using span_type             = typename const_mdspan_traits::transpose_mdspan_type;
        using const_span_type       = typename const_mdspan_traits::transpose_mdspan_type;

        // destructor
        ~MatrixViewEngine() noexcept = default;

        // default constructor
        constexpr MatrixViewEngine() noexcept
                : pReferentEngine_(nullptr)
        {}

        explicit constexpr MatrixViewEngine(EngineType& engine) noexcept
                : pReferentEngine_(&engine)
        {}

        // Move constructors
        constexpr MatrixViewEngine(MatrixViewEngine&&) noexcept = default;
        // Copy constructor
        constexpr MatrixViewEngine(MatrixViewEngine const&) noexcept = default;
        // Move assignment
        constexpr MatrixViewEngine&     operator =(MatrixViewEngine&&) noexcept = default;
        // Copy assignment
        constexpr MatrixViewEngine&     operator =(MatrixViewEngine const&) noexcept = default;

        constexpr bool
        isValid() const noexcept
        {
            return pReferentEngine_ != nullptr;
        }

        // ------------------  Size --------------------------------
        constexpr size_type    columns() const noexcept
        requires sizable_engine<EngineType>
        {
            return pReferentEngine_->rows();
        }
        constexpr size_type    rows() const noexcept
        requires sizable_engine<EngineType>
        {
            return pReferentEngine_->columns();
        }
        constexpr std::tuple<size_type, size_type>  size() const noexcept
        requires sizable_engine<EngineType>
        {
            return EngineType::size();
        }

        // ------------------  Element access --------------------------------
        constexpr const_reference     operator ()(size_type i, size_type j) const
        {
            return (*pReferentEngine_)(j, i);
        }


        // TODO: Do we need this? consider removing
        // ------------------  Modifiers  --------------------------------
        constexpr void          swap(MatrixViewEngine& rhs) noexcept
        {
            std::swap(pReferentEngine_, rhs.pReferentEngine_);
        }

    private:

        engine_pointer   pReferentEngine_;


    }; // class MatrixViewEngine<ET, matrix_view::const_transpose>






} // namespace pgeo

#endif //PGEOCL_MATRIXVIEWENGINE_H
