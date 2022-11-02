#ifndef PGEOCL_FORWARDDECLARATIONS_H
#define PGEOCL_FORWARDDECLARATIONS_H



namespace pgeo {


    // represents the scalar operand
    template<class T>   struct ScalarEngine;

    // Fixed-size matrix engine with owning internal storage
    template<class T, ptrdiff_t R, ptrdiff_t C> class MatrixEngine;


    template<class EngineType> class Matrix;

    template<class T, ptrdiff_t R, ptrdiff_t C>
    using Mat = Matrix<MatrixEngine<T, R, C>>;

    using Mat22f = Mat<float, 2, 2>;

    template <typename T>
    using Mat22 = Mat<T, 2, 2>;

    template <typename T>
    using Mat33 = Mat<T, 3, 3>;


} // namespace pgeo


#endif //PGEOCL_FORWARDDECLARATIONS_H
