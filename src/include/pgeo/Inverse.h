#ifndef PGEOCL_INVERSE_H
#define PGEOCL_INVERSE_H

#include <pgeo.h>

namespace pgeo {

    template<typename T, size_t N, typename L>
    using SquareMatrix = Matrix<MatrixEngine<T,N,N,L>>;

    /// Matrix Inversion
    template<std::floating_point T, size_t N, typename L>
    inline constexpr auto inverse(SquareMatrix<T,N,L> const& m) -> SquareMatrix<T,N,L>
    {
        if constexpr (N == 1){
            return 1. / m(0,0);
        } else {
            using size_type = typename SquareMatrix<T,N,L>::size_type;

            SquareMatrix<T,N,L>	  result = m;
            std::array<T,N>       iPivot{};
            std::array<T,N>       indexRow{};
            std::array<T,N>       indexCol{};

            for (size_type    i = 0;  i < N;  ++i) {
                size_type irow = 0;
                size_type icol = 0;
                T big = T();

                // choose pivot
                for (size_type j = 0; j < N; ++j) {
                    if (iPivot[j] != 1) {
                        for (size_type k = 0; k < N; ++k) {
                            if (iPivot[k] == 0) {
                                if (big <= std::abs(result(j, k))) {
                                    big = T(std::abs(result(j, k)));
                                    irow = j;
                                    icol = k;
                                }
                            } else if (iPivot[k] > 1) {
                                throw std::runtime_error("Matrix is singular");
                            }
                        }
                    }
                }
                ++iPivot[icol];
                // swap rows irow and icol for placing pivot in the diagonal
                result.swapRows(irow, icol);

                indexRow[i] = irow;
                indexCol[i] = icol;
                if (result(icol, icol) == 0) {
                    throw std::runtime_error("Matrix is singular");
                }
                // normalize $m(icol, icol)$ to one
                T invPivot = 1. / result(icol, icol);
                result(icol, icol) = 1.;
                for (size_type j = 0; j < N; ++j) {
                    result(icol, j) *= invPivot;
                }

                // Subtract current row from others to zero out their columns
                for (size_type j = 0; j < N; ++j) {
                    if (j != icol) {
                        T temp = result(j, icol);
                        result(j, icol) = 0;
                        for (size_type k = 0; k < N; ++k) {
                            result(j,k) -= result(icol, k) * temp;
                        }
                    }
                }
            }
            // Swap columns to reflect permutation
            for (size_type j = N ; j > 0; --j) {
                result.swapColumns(indexRow[j-1], indexCol[j-1]);
            }

            return result;
        }
    }




} // namespace pgeo


#endif //PGEOCL_INVERSE_H
