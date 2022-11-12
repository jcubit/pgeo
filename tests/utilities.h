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



#endif //PGEOCL_UTILITIES_H
