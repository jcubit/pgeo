#ifndef PGEOCL_ADDITION_H
#define PGEOCL_ADDITION_H

#include <pgeo.h>

namespace pgeo {

    /// Matrix Addition
    template<typename ET>
    inline constexpr auto operator +(Matrix<ET> const& m1, Matrix<ET> const& m2) -> Matrix<ET>
    {
        using size_type = typename Matrix<ET>::size_type;

        size_type    rows = m1.rows();
        size_type    cols = m1.columns();
        Matrix<ET>	  result;

        size_type    ir = 0;
        size_type    i1 = 0;
        size_type    i2 = 0;

        for (;  ir < rows;  ++ir, ++i1, ++i2)
        {
            size_type    jr = 0;
            size_type    j1 = 0;
            size_type    j2 = 0;

            for (;  jr < cols;  ++jr, ++j1, ++j2)
            {
                result(ir, jr) = m1(i1, j1) + m2(i2, j2);
            }
        }

        return result;
    }





} // namespace pgeo


#endif //PGEOCL_ADDITION_H
