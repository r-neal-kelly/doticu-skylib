/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/string.h"
#include "doticu_skylib/traits.h"

namespace doticu_skylib {

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
