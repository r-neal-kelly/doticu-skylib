/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    template <typename ...Ts>
    class traits_wrap_t
    {
    public:
    };

    // arithmetic
    template <typename T>
    using enable_if_arithmetic_t = std::enable_if_t<
        std::is_arithmetic<T>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_arithmetic :
        public std::false_type
    {
    };
    template <typename T>
    struct is_arithmetic<T, std::conditional_t<false, enable_if_arithmetic_t<T>, void>> :
        public std::true_type
    {
    };

    // arrayable
    template <typename T>
    using arrayable_traits_t = traits_wrap_t<
        typename T::value_type,
        typename T::size_type,
        decltype(std::declval<T>().size())
    >;
    template <typename T, typename _ = void>
    struct is_arrayable :
        public std::false_type
    {
    };
    template <typename T>
    struct is_arrayable<T, std::conditional_t<false, arrayable_traits_t<T>, void>> :
        public std::true_type
    {
    };
    template <typename T>
    using enable_if_arrayable_t = std::enable_if_t<
        is_arrayable<T>::value,
        Bool_t
    >;

    // boolean
    template <typename T>
    using enable_if_boolean_t = std::enable_if_t<
        std::is_same<T, bool>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_boolean :
        public std::false_type
    {
    };
    template <typename T>
    struct is_boolean<T, std::conditional_t<false, enable_if_boolean_t<T>, void>> :
        public std::true_type
    {
    };

    // class
    template <typename T>
    using enable_if_class_t = std::enable_if_t<
        std::is_class<T>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_class :
        public std::false_type
    {
    };
    template <typename T>
    struct is_class<T, std::conditional_t<false, enable_if_class_t<T>, void>> :
        public std::true_type
    {
    };

    template <typename T>
    using enable_if_not_class_t = std::enable_if_t<
        !is_class<T>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct isnt_class :
        public std::false_type
    {
    };
    template <typename T>
    struct isnt_class<T, std::conditional_t<false, enable_if_not_class_t<T>, void>> :
        public std::true_type
    {
    };

    // convertible
    template <typename From, typename To>
    using enable_if_convertible_t = std::enable_if_t<
        std::is_convertible<From, To>::value,
        Bool_t
    >;
    template <typename From, typename To, typename _ = void>
    struct is_convertible :
        public std::false_type
    {
    };
    template <typename From, typename To>
    struct is_convertible<From, To, std::conditional_t<false, enable_if_convertible_t<From, To>, void>> :
        public std::true_type
    {
    };

    // enum
    template <typename T>
    using enable_if_enum_t = std::enable_if_t<
        std::is_enum<T>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_enum :
        public std::false_type
    {
    };
    template <typename T>
    struct is_enum<T, std::conditional_t<false, enable_if_enum_t<T>, void>> :
        public std::true_type
    {
    };

    // enumable
    template <typename T>
    using enable_if_enumable_t = std::enable_if_t<
        std::is_integral<T>::value &&
        !std::is_same<T, Bool_t>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_enumable :
        public std::false_type
    {
    };
    template <typename T>
    struct is_enumable<T, std::conditional_t<false, enable_if_enumable_t<T>, void>> :
        public std::true_type
    {
    };

    // f32
    template <typename T>
    using enable_if_f32_t = std::enable_if_t<
        std::is_same<T, f32>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_f32 :
        public std::false_type
    {
    };
    template <typename T>
    struct is_f32<T, std::conditional_t<false, enable_if_f32_t<T>, void>> :
        public std::true_type
    {
    };

    // f64
    template <typename T>
    using enable_if_f64_t = std::enable_if_t<
        std::is_same<T, f64>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_f64 :
        public std::false_type
    {
    };
    template <typename T>
    struct is_f64<T, std::conditional_t<false, enable_if_f64_t<T>, void>> :
        public std::true_type
    {
    };

    // floating_point
    template <typename T>
    using enable_if_floating_point_t = std::enable_if_t<
        is_f32<T>::value ||
        is_f64<T>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_floating_point :
        public std::false_type
    {
    };
    template <typename T>
    struct is_floating_point<T, std::conditional_t<false, enable_if_floating_point_t<T>, void>> :
        public std::true_type
    {
    };

    // i32_or_less
    template <typename T>
    using enable_if_i32_or_less_t = std::enable_if_t<
        std::is_same<T, u8>::value ||
        std::is_same<T, u16>::value ||
        std::is_same<T, u32>::value ||
        std::is_same<T, s8>::value ||
        std::is_same<T, s16>::value ||
        std::is_same<T, s32>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_i32_or_less :
        public std::false_type
    {
    };
    template <typename T>
    struct is_i32_or_less<T, std::conditional_t<false, enable_if_i32_or_less_t<T>, void>> :
        public std::true_type
    {
    };

    // iterable
    template <typename T>
    using iterable_traits_t = traits_wrap_t<
        typename T::value_type,
        decltype(std::declval<T>().begin()),
        decltype(std::declval<T>().end())
    >;
    template <typename T, typename _ = void>
    struct is_iterable :
        public std::false_type
    {
    };
    template <typename T>
    struct is_iterable<T, std::conditional_t<false, iterable_traits_t<T>, void>> :
        public std::true_type
    {
    };
    template <typename T>
    using enable_if_iterable_t = std::enable_if_t<
        is_iterable<T>::value,
        Bool_t
    >;

    // pointer
    template <typename T>
    using enable_if_pointer_t = std::enable_if_t<
        std::is_pointer<T>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_pointer :
        public std::false_type
    {
    };
    template <typename T>
    struct is_pointer<T, std::conditional_t<false, enable_if_pointer_t<T>, void>> :
        public std::true_type
    {
    };

    template <typename T>
    using enable_if_not_pointer_t = std::enable_if_t<
        !is_pointer<T>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct isnt_pointer :
        public std::false_type
    {
    };
    template <typename T>
    struct isnt_pointer<T, std::conditional_t<false, enable_if_not_pointer_t<T>, void>> :
        public std::true_type
    {
    };

    // s64_or_less
    template <typename T>
    using enable_if_s64_or_less_t = std::enable_if_t<
        std::is_same<T, s8>::value ||
        std::is_same<T, s16>::value ||
        std::is_same<T, s32>::value ||
        std::is_same<T, s64>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_s64_or_less :
        public std::false_type
    {
    };
    template <typename T>
    struct is_s64_or_less<T, std::conditional_t<false, enable_if_s64_or_less_t<T>, void>> :
        public std::true_type
    {
    };

    // signed
    template <typename T>
    using enable_if_signed_t = std::enable_if_t<
        std::is_integral<T>::value &&
        std::is_signed<T>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_signed :
        public std::false_type
    {
    };
    template <typename T>
    struct is_signed<T, std::conditional_t<false, enable_if_signed_t<T>, void>> :
        public std::true_type
    {
    };

    // unsigned
    template <typename T>
    using enable_if_unsigned_t = std::enable_if_t<
        std::is_integral<T>::value&&
        std::is_unsigned<T>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_unsigned :
        public std::false_type
    {
    };
    template <typename T>
    struct is_unsigned<T, std::conditional_t<false, enable_if_unsigned_t<T>, void>> :
        public std::true_type
    {
    };

    // void
    template <typename T>
    using enable_if_void_t = std::enable_if_t<
        std::is_void<T>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_void :
        public std::false_type
    {
    };
    template <typename T>
    struct is_void<T, std::conditional_t<false, enable_if_void_t<T>, void>> :
        public std::true_type
    {
    };

}
