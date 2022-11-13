#ifndef PGEOCL_UTILITIES_H
#define PGEOCL_UTILITIES_H

#include "pgeo.h"
#include "spdlog/spdlog.h"
#include <span>





template <typename T, size_t R, size_t C>
void print(const pgeo::Mat<T,R,C>& m, std::string message = "")
{
    spdlog::info(message + "{}", std::move(m));
}




// -------- Format for Matrix log output----------------------------------------------------------------

template <size_t R, size_t C>
std::string matrix_string_format(std::string prefix, uint32_t precision, std::string separator)
{
    std::string s{prefix};
    //s += "\n";
    for(size_t i = 0; i < R; ++i){
        s += "[";
        for(size_t j = 0; j < C; ++j) {
            s += "{: .";
            s += std::to_string(precision);
            s += "f}";
            if (j != C - 1){
                s += separator;
            } else {
                s += " ]";
            }
        }
        if (i != R - 1)
        {
            s += "\n";
        }
    }
    return s;
}



template <typename OutputIt, typename T, size_t R, size_t C, std::size_t... I>
auto format_to_matrix_impl(OutputIt outputIt,
                           pgeo::Mat<T, R, C>& matrix,
                           std::index_sequence<I...>,
                           std::string prefix = "\n",
                           uint32_t precision = 3,
                           std::string separator = ",") -> OutputIt
{
    std::array<T, R*C> array{};
    auto matrixSpan = matrix.span();
    for(size_t i=0; i< matrixSpan.extent(0); i++){
        for(size_t j=0; j< matrixSpan.extent(1); j++){
            array[i*C + j] = matrixSpan(i, j);
        }
    }

    std::string matrix_format = matrix_string_format<R,C>(prefix, precision, separator);
    return fmt::format_to(outputIt, matrix_format, array[I]...);
}

template <typename OutputIt, typename T, size_t R, size_t C, typename Indices = std::make_index_sequence<R*C>>
auto format_to_matrix(OutputIt outputIt, pgeo::Mat<T,R,C> matrix) -> OutputIt
{
    return format_to_matrix_impl(outputIt, matrix, Indices{});
}


template<typename T, size_t R, size_t C>
struct fmt::formatter<pgeo::Mat<T,R,C>> : fmt::formatter<std::string>
{

    auto format(pgeo::Mat<T,R,C> matrix, format_context &ctx) -> decltype(ctx.out())
    {
        return format_to_matrix(ctx.out(), matrix);
    }
};


// ------ Concepts Debug --------------------------------
// We want to find out which constructor is called when we copy assign a TransposeView2f to a Mat2f
namespace pgeo
{

    template<typename T, size_t R, size_t C>
    using TransposeView = Matrix
            <MatrixViewEngine<
                    MatrixEngine<T,
                            R, C,
                            matrix_layout::row_major>,
                    matrix_view::transpose>>;

    using TransposeView2f = TransposeView<float,2,2>;


    static_assert(std::constructible_from<Mat2f ,TransposeView2f>);
    static_assert(mutable_matrix_engine<Mat2f>);
    static_assert(matrix_engine<TransposeView2f>);

    // The following constructor is called!

//    template <typename EngineType2>
//    constexpr Matrix(Matrix<EngineType2> const& src)
//    requires
//    mutable_matrix_engine<EngineType>
//    and
//    std::constructible_from<EngineType, EngineType2>
//            : engine_(src.engine_) {}
}


#endif //PGEOCL_UTILITIES_H
