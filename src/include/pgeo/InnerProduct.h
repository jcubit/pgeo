#ifndef PGEOCL_SCALARPRODUCT_H
#define PGEOCL_SCALARPRODUCT_H

#include <pgeo.h>

namespace pgeo {


    template<typename ET>
    requires (not ET::is_vector_or_covector)
    inline constexpr auto innerProduct(Matrix<ET> const &m1, Matrix<ET> const &m2) -> typename ET::element_type
    {
        using size_type = typename Matrix<ET>::size_type;
        using element_type = typename ET::element_type;

        size_type     rows  = m1.rows();
        size_type     cols  = m2.columns();
        element_type  result{};

        for (size_type  i = 0;  i < rows;  ++i)
        {
            for (size_type  j = 0;  j < cols;  ++j)
            {
                result += (m1(i, j) * m2(i, j));
            }
        }
        return result;
    }

}


#endif //PGEOCL_SCALARPRODUCT_H
