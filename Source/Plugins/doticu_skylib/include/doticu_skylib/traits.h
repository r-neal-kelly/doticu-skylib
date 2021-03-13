/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    template <typename ...Ts>
    class traits_wrap_t
    {
    public:
    };

    template <typename T>
    using iterable_traits_t = traits_wrap_t<
        typename T::value_type,
        decltype(std::declval<T>().begin()),
        decltype(std::declval<T>().end())
    >;

    template <typename T, typename _ = void>
    class is_iterable : public std::false_type
    {
    public:
    };

    template <typename T>
    class is_iterable<T, std::conditional_t<false, iterable_traits_t<T>, void>> : public std::true_type
    {
    public:
    };

    template <typename T>
    using arrayable_traits_t = traits_wrap_t<
        typename T::value_type,
        typename T::size_type,
        decltype(std::declval<T>().size())
    >;

    template <typename T, typename _ = void>
    class is_arrayable : public std::false_type
    {
    public:
    };

    template <typename T>
    class is_arrayable<T, std::conditional_t<false, arrayable_traits_t<T>, void>> : public std::true_type
    {
    public:
    };

    template <typename T>
    using enable_if_iterable_t = std::enable_if_t<
        is_iterable<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_arrayable_t = std::enable_if_t<
        is_arrayable<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_void_t = std::enable_if_t <
        std::is_void<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_pointer_t = std::enable_if_t<
        std::is_pointer<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_not_pointer_t = std::enable_if_t<
        !std::is_pointer<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_boolean_t = std::enable_if_t<
        std::is_same<T, bool>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_integer_32_or_less_t = std::enable_if_t<
        std::is_same<T, u8>::value ||
        std::is_same<T, u16>::value ||
        std::is_same<T, u32>::value ||
        std::is_same<T, s8>::value ||
        std::is_same<T, s16>::value ||
        std::is_same<T, s32>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_enum_32_or_less_t = std::enable_if_t<
        (std::is_enum<T>::value ||
         std::is_convertible<T, Enum_t<typename T::value_type>>::value) &&
        (std::is_same<typename T::value_type, u8>::value ||
         std::is_same<typename T::value_type, u16>::value ||
         std::is_same<typename T::value_type, u32>::value ||
         std::is_same<typename T::value_type, s8>::value ||
         std::is_same<typename T::value_type, s16>::value ||
         std::is_same<typename T::value_type, s32>::value),
        Bool_t
    >;

    template <typename T>
    using enable_if_enum_t = std::enable_if_t<
        std::is_enum<T>::value ||
        std::is_convertible<T, Enum_t<typename T::value_type>>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_float_32_t = std::enable_if_t<
        std::is_same<T, f32>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_not_pointer_and_not_arithmetic = std::enable_if_t<
        !std::is_pointer<T>::value &&
        !std::is_arithmetic<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_integral_t = std::enable_if_t<
        std::is_integral<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_signed_integral_t = std::enable_if_t<
        std::is_integral<T>::value &&
        std::is_signed<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_unsigned_integral_t = std::enable_if_t<
        std::is_integral<T>::value &&
        std::is_unsigned<T>::value,
        Bool_t
    >;

    template <typename From, typename To>
    using enable_if_convertible_t = std::enable_if_t<
        std::is_convertible<From, To>::value,
        Bool_t
    >;

    template <typename T, typename _ = void>
    struct is_signed_integral : public std::false_type {};
    template <typename T>
    struct is_signed_integral<T, std::conditional_t<false, enable_if_signed_integral_t<T>, void>> : public std::true_type {};

    template <typename T, typename _ = void>
    struct is_unsigned_integral : public std::false_type {};
    template <typename T>
    struct is_unsigned_integral<T, std::conditional_t<false, enable_if_unsigned_integral_t<T>, void>> : public std::true_type {};

    template <typename T, typename _ = void>
    struct is_integer_32_or_less : public std::false_type {};
    template <typename T>
    struct is_integer_32_or_less<T, std::conditional_t<false, enable_if_integer_32_or_less_t<T>, void>> : public std::true_type {};

    template <typename T, typename _ = void>
    struct is_enum_32_or_less : public std::false_type {};
    template <typename T>
    struct is_enum_32_or_less<T, std::conditional_t<false, enable_if_enum_32_or_less_t<T>, void>> : public std::true_type {};

    template <typename T, typename _ = void>
    struct is_enum : public std::false_type {};
    template <typename T>
    struct is_enum<T, std::conditional_t<false, enable_if_enum_t<T>, void>> : public std::true_type {};

    template <typename T>
    using enable_if_virtual_bool_t = enable_if_boolean_t<T>;

    template <typename T>
    using enable_if_virtual_int_t = std::enable_if_t<
        is_integer_32_or_less<T>::value ||
        is_enum<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_virtual_float_t = enable_if_float_32_t<T>;

    template <typename T>
    using enable_if_virtual_string_t = std::enable_if_t<
        std::is_same<T, String_t>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_virtual_script_t = enable_if_pointer_t<T>;

}
