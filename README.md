![logo_pgeo](logo_pgeo.png)

## Description

`pgeo` is a C++ project for a projective geometry library in $RP^3$. `pgeo` is inspired by the [proposal](https://wg21.link/p1385) of adding a linear algebra support to the standard C++ library, which is targeted for C++26. This library implements a subset of that proposal. Since the focus here is $RP^3$ the matrix sizes are known at compile time, and we can add different static matrix engines with the same Matrix API.

## Why would somebody be interested nowadays in writing a C++ Math library?

At the moment of writing this, the C++ standard library does *not* provide any facilities for doing basic linear algebra. That is, there is no out-of-the-box support for transforming vectors and doing simple matrix multiplications. This might sound surprising to anyone new to C++ and to people coming from another language where this is naturally supported. 

You might then resource to popular third-party libraries like [Eigen] (https://eigen.tuxfamily.org/index.php?title=Main_Page), [Blaze](https://bitbucket.org/blaze-lib/blaze/src/master/) and [BLAS](https://netlib.org/blas/). These are excellent options, but they are only partially cost-free. The "expression templates" technique, on which these libraries are built, might be inappropriate for the type of applications you are working. Moreover, these libraries might not have a clean way to interface with the STL, which means that it's messy, for example, to use the standard algorithms and range libraries. Finally, let's say you need to use new fundamental math types from another library or customize the implementation details for a specific operation. How could you do this without falling into a cascade of changes?

These issues are what the proposal PR1385 tries to address. It wants to provide a standard linear algebra library that separates implementation details from a clean common public interface. PGEO is an excuse to study the architecture design of this proposal with modern C++ and learn more about template metaprogramming and mdspan (other proposal for multi-dimensional spans). 
