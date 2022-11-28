#ifndef PGEOCL_DETERMINANT_H
#define PGEOCL_DETERMINANT_H

#include <pgeo.h>


namespace pgeo
{

    /// 2x2 Matrix Determinant
    template<std::floating_point T, typename L>
    inline constexpr auto determinant(const SquareMatrix<T,2,L>& m) -> T
    {
        return m(0,0)*m(1,1) - m(0,1)*m(1,0);
    }

    template<std::floating_point T>
    inline constexpr auto determinant(T m00, T m01, T m10, T m11) -> T
    {
        return m00*m11 - m01*m10;
    }

    /// 3x3 Matrix Determinant
    template<std::floating_point T, typename L>
    inline constexpr auto determinant(const SquareMatrix<T,3,L>& m) -> T
    {
        T a =  m(0,0) * determinant(m(1,1), m(1,2), m(2,1), m(2,2));
        T b = -m(0,1) * determinant(m(1,0), m(1,2), m(2,0), m(2,2));
        T c =  m(0,2) * determinant(m(1,0), m(1,1), m(2,0), m(2,1));

        return a + b + c;
    }

    /// 3x3 Matrix Determinant
    template<one_dimensional_matrix VectorType>
    inline constexpr auto determinant(VectorType v1, VectorType v2, VectorType v3) -> typename VectorType::element_type
    {
        using element_type = typename VectorType::element_type;

        element_type a =  v1(0) * determinant(v2(1), v2(2), v3(1), v3(2));
        element_type b = -v1(1) * determinant(v2(0), v2(2), v3(0), v3(2));
        element_type c =  v1(2) * determinant(v2(0), v2(1), v3(0), v3(1));

        return a + b + c;
    }

    /// 4x4 Matrix Determinant
    template<one_dimensional_matrix VectorType>
    inline constexpr auto determinant(VectorType v1, VectorType v2, VectorType v3, VectorType v4) -> typename VectorType::element_type
    {
        using element_type = typename VectorType::element_type;

        element_type a =  v1(0) * determinant(Vec<element_type,3>({v2(1),v2(2),v2(3)}),
                                              Vec<element_type,3>({v3(1),v3(2),v3(3)}),
                                              Vec<element_type,3>({v4(1),v4(2),v4(3)}));
        element_type b = -v1(1) * determinant(Vec<element_type,3>({v2(0),v2(2),v2(3)}),
                                              Vec<element_type,3>({v3(0),v3(2),v3(3)}),
                                              Vec<element_type,3>({v4(0),v4(2),v4(3)}));
        element_type c =  v1(2) * determinant(Vec<element_type,3>({v2(0),v2(1),v2(3)}),
                                              Vec<element_type,3>({v3(0),v3(1),v3(3)}),
                                              Vec<element_type,3>({v4(0),v4(1),v4(3)}));
        element_type d =  -v1(3) * determinant(Vec<element_type,3>({v2(0),v2(1),v2(2)}),
                                               Vec<element_type,3>({v3(0),v3(1),v3(2)}),
                                               Vec<element_type,3>({v4(0),v4(1),v4(2)}));

        return a + b + c + d;
    }

} // namespace pgeo

#endif //PGEOCL_DETERMINANT_H
