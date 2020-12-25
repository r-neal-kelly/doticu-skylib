/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PapyrusArgs.h"
#include "skse64/PapyrusNativeFunctions.h"
#include "skse64/PapyrusVM.h"

#include "doticu_skylib/skylib.h"

namespace doticu_skylib { namespace Virtual {

    using Registry_t        = VMClassRegistry;

    using Stack_ID_t        = u32;
    using Raw_Handle_t      = u64;

    class Arguments_t;
    class Array_t;
    class Callback_i;
    class Callback_t;
    class Class_t;
    class Machine_t;
    class Object_t;
    class Utils_t;
    class Variable_t;

    class Bool_Variable_t;
    class Int_Variable_t;
    class Float_Variable_t;
    class String_Variable_t;
    template <typename T>
    class Array_Variable_t;

}}

namespace doticu_skylib { namespace Virtual {

    template <typename T>
    using enable_if_virtual_bool_t      = enable_if_boolean_t<T>;
    template <typename T>
    using enable_if_virtual_int_t       = enable_if_integer_32_or_less_t<T>;
    template <typename T>
    using enable_if_virtual_float_t     = enable_if_float_32_or_less_t<T>;
    template <typename T>
    using enable_if_virtual_string_t    = std::enable_if_t<std::is_same<T, String_t>::value, Bool_t>;
    template <typename T>
    using enable_if_virtual_script_t    = enable_if_pointer_t<T>;
    template <typename T>
    using enable_if_other_virtual_t     = enable_if_not_pointer_and_not_arithmetic<T>;

}}
