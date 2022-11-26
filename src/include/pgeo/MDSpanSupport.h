#ifndef PGEOCL_MDSPANSUPPORT_H
#define PGEOCL_MDSPANSUPPORT_H


namespace pgeo
{

    namespace support
    {
        // Helper functions to get the type of the owning Engine span type
        template<class ET>
        using get_mdspan_type_t = typename ET::span_type;

        template<class ET>
        using get_const_mdspan_type_t = typename ET::const_span_type;


        template<typename T>
        struct mdspan_view_traits;

        template <typename T, size_t N, size_t M, typename Layout, typename Accessor>
        struct mdspan_view_traits<stdex::basic_mdspan<T, stdex::extents<N, M>, Layout, Accessor>>
        {
            using transpose_extents = stdex::extents<M, N>;
            // the stride is in terms of offset index to get to the next row/column
            using transpose_layout_stride = stdex::layout_stride<1 , N>;
            using transpose_mdspan_type = stdex::basic_mdspan<T, transpose_extents, transpose_layout_stride, Accessor>;

            template<typename EngineSpanType>
            static constexpr auto make_transpose(const EngineSpanType& s) -> transpose_mdspan_type
            {
                using transpose_mapping = typename transpose_layout_stride::template mapping<transpose_extents>;
                transpose_extents        extents{};
                transpose_mapping        mapping{};

                return transpose_mdspan_type(s.data(), mapping, Accessor());
            }

        }; // struct mdspan_view_traits





    }


} // namespace pgeo

#endif //PGEOCL_MDSPANSUPPORT_H
