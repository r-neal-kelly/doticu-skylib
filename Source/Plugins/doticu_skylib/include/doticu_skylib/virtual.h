/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/skylib.h"
#include "doticu_skylib/virtual_traits.h"

namespace doticu_skylib { namespace Virtual {

    using Raw_Handle_t      = u64;

    class Type_e;

    class Arguments_i;
    class Arguments_t;
    class Array_t;
    class Callback_i;
    class Callback_t;
    class Class_t;
    class Debug_t;
    class Handle_t;
    class Handle_Policy_t;
    class Input_t;
    class Latent_ID_t;
    class Machine_t;
    class Object_t;
    class Object_Policy_t;
    class Stack_ID_t;
    class Utility_t;
    class Variable_t;

    template <typename ...Ts>
    using Callback_ii = doticu_skylib::Callback_i<Ts...>;
    template <typename T>
    class Variable_tt;

}}
