#ifndef PGEOCL_VECTOR3_H
#define PGEOCL_VECTOR3_H

#include <initializer_list>
#include <span>


namespace pgeo {

    template <typename T>
    struct Vector3 {

        using element_type = T;
        using value_type = std::remove_cv_t<T>;
        using pointer = element_type*;
        using const_pointer = element_type const*;
        using reference = element_type&;
        using const_reference = element_type const&;
        using difference_type = ptrdiff_t; // proper type for the difference between iterators
        using size_type = size_t;
        using index_type = ptrdiff_t;
        using span_type = std::span<element_type, 3>;
        using const_span_type = std::span<element_type const, 3>;

        // destructor
        ~Vector3() = default;

        // default constructor
        constexpr Vector3();

        // move constructor
        constexpr Vector3(Vector3&&) noexcept = default;

        // Copy constructor
        constexpr Vector3(Vector3 const&) = default;

        // constructor with initialization list (without type conversion)
        constexpr Vector3(std::initializer_list<element_type> list);

        // move assignment
        constexpr Vector3& operator=(Vector3&&) noexcept = default;

        // copy assignment
        constexpr Vector3& operator=(Vector3 const&) = default;

        // Assignment with initialization list (without type conversion)
        constexpr Vector3& operator=(std::initializer_list<element_type> list);


        constexpr reference			operator()(index_type i);
        constexpr const_reference	operator()(index_type i) const;

        // ------------------  Data access --------------------------
        constexpr span_type			span() noexcept;
        constexpr const_span_type	span() const noexcept;

        // ------------------  Modifiers  --------------------------
        constexpr void swapElements(index_type i, index_type j) noexcept;

    private:
        std::array<element_type , 3>						data_;

    }; // struct Vector3


    // Constructors ------------------------------------------------------
    template<typename T>
    constexpr Vector3<T>::Vector3()
            : data_() {}


    template <typename T>
    constexpr Vector3<T>::Vector3(std::initializer_list<T> list)
    {
        using elem_iter_src = decltype(list.begin());

        elem_iter_src sourceIt = list.begin();

        for (index_type i = 0; i < 3; ++i, ++sourceIt)
        {
            data_[i] = static_cast<Vector3::element_type>(*sourceIt);
        }
    }

    template <typename T>
    constexpr Vector3<T> &Vector3<T>::operator=(std::initializer_list<element_type> list)
    {
        using elem_iter_src = decltype(list.begin());

        elem_iter_src sourceIt = list.begin();

        for (index_type i = 0; i < 3; ++i, ++sourceIt)
        {
            data_[i] = static_cast<Vector3::element_type>(*sourceIt);
        }

        return *this;
    }

    template <typename T>
    constexpr auto Vector3<T>::operator()(index_type i) -> reference
    {
        return data_[i];
    }

    template <typename T>
    constexpr auto Vector3<T>::operator()(index_type i) const -> const_reference
    {
        return data_[i];
    }

    template<typename T>
    constexpr auto Vector3<T>::span() noexcept -> span_type
    {
        return span_type(data_);
    }

    template<typename T>
    constexpr auto Vector3<T>::span() const noexcept -> const_span_type
    {
        return const_span_type(data_);
    }

    template<typename T>
    constexpr void Vector3<T>::swapElements(index_type i, index_type j) noexcept
    {
        std::swap(data_[i], data_[j]);
    }


    // -----------------------------------------------------------------------------------------------
    // ------------------- Explicit Instantiations --------------------------------------------------

    template class Vector3<double>;
    using Vec3d = Vector3<double>;

} // namespace pgeo





#endif //PGEOCL_VECTOR3_H
