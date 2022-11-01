#ifndef PGEOCL_PRIVATESUPPORT_H
#define PGEOCL_PRIVATESUPPORT_H

#include <pgeo.h>

namespace pgeo
{

    // Helper functions to be used inside engine member functions to validate a source engine or initializer list prior to
    // a destination engine. If validation fails they will cause a compile-time error evaluated in a constexpr context
    // --- Vector ---
    template<typename ET, typename SourceT>
    inline constexpr void check_source_engine_size(ET const& engine, SourceT numberOfElements)
    {
        static_assert(engine.size() == numberOfElements,
                      "Source engine size does not match destination vector engine size");
    }

    template <typename T, typename SourceT>
    inline constexpr void check_source_init_list(std::initializer_list<T> list,
                                                 SourceT numberOfElements)
    {
        if (list.size() != static_cast<size_t>(numberOfElements)) {
            throw std::runtime_error("initializer_list size does not match vector engine size");
        }
    }

    // --- Matrix ---
    template <typename T, typename SourceT>
    inline constexpr void check_source_init_list(std::initializer_list<std::initializer_list<T>> matrixList,
                                                 SourceT rows,
                                                 SourceT columns)
    {
        size_t firstRowSize = matrixList.begin()->size();

        for (auto const row : matrixList)
        {
            if(row.size() != firstRowSize) {
                throw std::runtime_error("Source 2D initializer_list has invalid shape. Not all rows have the same size.");
            }

        }

        if (matrixList.size() != static_cast<size_t>(rows)
            || firstRowSize != static_cast<size_t>(columns)) {
            throw std::runtime_error("Source 2D initializer_list size does not match with the destination matrix engine size");
        }

    }

    template<class ET, class ST>
    constexpr void check_source_engine_size(ET const& engine, ST rows, ST cols)
    {
        static_assert(engine.rows() == rows && engine.columns() == cols,
                      "source engine size does not match destination matrix engine size");
    }

    // Helper function to be used inside member functions to perform a generic assignment of elements to a destination
    // engine from a source engine or initializer list. It should be used after calling the check helper functions as
    // here no checking is done.
    template <typename ET1, typename ET2>
    constexpr void assign_from_vector_engine(ET1& dst, ET2 const& src)
    {
        using elem_type_dst = typename ET1::element_type;
        using index_type_dst = typename ET1::index_type;
        using index_type_src = typename ET2::index_type;

        index_type_dst di = 0;
        index_type_src si = 0;
        index_type_src ni = src.size();

        for (; si < ni; ++di, ++si)
        {
            dst(di) = static_cast<elem_type_dst>(src(si));
        }

    }




    // --- Matrix ---
    /// Copies the matrix elements to the destination type and assigns them
    /// to the destination matrix. It does not matter how big the source matrix is
    /// it copies only the size elements of the destination matrix
    template <typename ET1, typename ET2>
    constexpr void assign_from_matrix_engine(ET1& dst, ET2 const& src)
    {
        using elem_type_dst = typename ET1::element_type;
        using index_type_dst = typename ET1::index_type;
        using index_type_src = typename ET2::index_type;

        index_type_dst di = 0;
        index_type_src si = 0;
        index_type_src ni = src.size();

        for (; si < ni; ++di, ++si)
        {
            dst(di) = static_cast<elem_type_dst>(src(si));
        }
    }

    template<class ET, class T>
    constexpr void assign_from_matrix_initlist(ET& engine, std::initializer_list<std::initializer_list<T>> rhs)
    {
        using elem_type_dst  = typename ET::element_type;
        using index_type_dst = typename ET::index_type;
        using row_iter_src   = decltype(rhs.begin());
        using col_iter_src   = decltype(rhs.begin()->begin());

        index_type_dst  dstRow = 0;
        row_iter_src    srcRow = rhs.begin();

        for (;  dstRow < engine.rows();  ++dstRow, ++srcRow)
        {
            index_type_dst  dstColumn = 0;
            col_iter_src    srcColumn = srcRow->begin();

            for (;  dstColumn < engine.columns();  ++dstColumn, ++srcColumn)
            {
                engine(dstRow, dstColumn) = static_cast<elem_type_dst>(*srcColumn);
            }
        }
    }


} // namespace pgeo


#endif //PGEOCL_PRIVATESUPPORT_H
