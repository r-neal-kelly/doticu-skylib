/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/enum_type.h"
#include "doticu_skylib/string.h"
#include "doticu_skylib/traits.h"

namespace doticu_skylib {

    template <typename T>
    using enable_if_any_enum_t = std::enable_if_t<
        std::is_enum<T>::value ||
        is_enum<T>::value ||
        is_enum_type<T>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_any_enum :
        public std::false_type
    {
    };
    template <typename T>
    struct is_any_enum<T, std::conditional_t<false, enable_if_any_enum_t<T>, void>> :
        public std::true_type
    {
    };

    template <typename T>
    using enable_if_any_enum_32_or_less_t = std::enable_if_t<
        is_any_enum<T>::value &&
        (std::is_same<typename T::value_type, u8>::value ||
         std::is_same<typename T::value_type, u16>::value ||
         std::is_same<typename T::value_type, u32>::value ||
         std::is_same<typename T::value_type, s8>::value ||
         std::is_same<typename T::value_type, s16>::value ||
         std::is_same<typename T::value_type, s32>::value),
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_any_enum_32_or_less :
        public std::false_type
    {
    };
    template <typename T>
    struct is_any_enum_32_or_less<T, std::conditional_t<false, enable_if_any_enum_32_or_less_t<T>, void>> :
        public std::true_type
    {
    };

    template <typename T>
    using enable_if_virtual_bool_t = enable_if_boolean_t<T>;

    template <typename T>
    using enable_if_virtual_int_t = std::enable_if_t<
        is_i32_or_less<T>::value ||
        is_any_enum<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_virtual_float_t = enable_if_f32_t<T>;

    template <typename T>
    using enable_if_virtual_string_t = std::enable_if_t<
        std::is_same<T, String_t>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_virtual_script_t = enable_if_pointer_t<T>;

}
