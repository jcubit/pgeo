#ifndef PGEOCL_MULTIPLICATION_H
#define PGEOCL_MULTIPLICATION_H

#include <pgeo.h>

namespace pgeo {


    template<typename ET>
    requires (not ET::is_vector_or_covector)
    inline constexpr auto operator *(Matrix<ET> const& m1, Matrix<ET> const& m2) -> Matrix<ET>
    {
        // TODO: throw exception if they are both vectors or covectors.
        using size_type = typename Matrix<ET>::size_type;

        size_type     rows  = m1.rows();
        size_type     cols  = m2.columns();
        Matrix<ET>	  result;

        size_type     ir = 0;
        size_type     i1 = 0;

        for (;  ir < rows;  ++ir, ++i1)
        {
            size_type     jr = 0;
            size_type     j2 = 0;

            for (;  jr < cols;  ++jr, ++j2)
            {
                typename Matrix<ET>::element_type    sum{};
                size_type     k1 = 0;
                size_type     k2 = 0;

                for (k1 = 0, k2 = 0;  k1 < cols;  ++k1, ++k2)
                {
                    sum = sum + (m1(i1, k1) * m2(k2, j2));
                }

                result(ir, jr) = sum;
            }
        }
        return result;
    }

    template<typename U, typename ET>
    requires std::convertible_to<U, typename ET::element_type>
    inline constexpr auto operator *(U scalar, Matrix<ET> const& m) -> Matrix<ET>
    {
        using size_type = typename Matrix<ET>::size_type;

        size_type     rows  = m.rows();
        size_type     cols  = m.columns();
        Matrix<ET>	  result;

        size_type     ir = 0;
        size_type     i = 0;

        for (;  ir < rows;  ++ir, ++i)
        {
            size_type     jr = 0;
            size_type     j = 0;

            for (;  jr < cols;  ++jr, ++j)
            {
                result(ir, jr) = scalar * m(i,j);
            }
        }
        return result;
    }

    template<typename U, typename ET>
    requires std::convertible_to<U, typename ET::element_type>
    inline constexpr auto operator *(Matrix<ET> const& m, U scalar) -> Matrix<ET>
    {
        using size_type = typename Matrix<ET>::size_type;

        size_type     rows  = m.rows();
        size_type     cols  = m.columns();
        Matrix<ET>	  result;

        size_type     ir = 0;
        size_type     i = 0;

        for (;  ir < rows;  ++ir, ++i)
        {
            size_type     jr = 0;
            size_type     j = 0;

            for (;  jr < cols;  ++jr, ++j)
            {
                result(ir, jr) = scalar * m(i,j);
            }
        }
        return result;
    }




} // namespace pgeo

#endif //PGEOCL_MULTIPLICATION_H