#ifndef PGEOCL_PGEO_H
#define PGEOCL_PGEO_H


#include <experimental/mdspan>
namespace stdex = std::experimental;

#include <array>
#include <initializer_list>
#include <type_traits>
#include <tuple>
#include <concepts>


namespace pgeo {

    struct matrix_layout
    {
        struct row_major {};
        struct column_major {};
        struct unknown{};
    };

    // Matrix view Tags
    struct matrix_view
    {
        struct const_negation {};
        struct transpose {};
        struct const_transpose {};

        struct submatrix {};
        struct const_submatrix {};
    };

} // namespace pgeo

#include "pgeo/MDSpanSupport.h"
#include "pgeo/MatrixEngineSupport.h"
#include "pgeo/MatrixEngine.h"
#include "pgeo/MatrixViewEngine.h"
#include "pgeo/Matrix.h"

#include "pgeo/Addition.h"
#include "pgeo/Multiplication.h"
#include "pgeo/Inverse.h"





#endif //PGEOCL_PGEO_H
