/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/skylib.h"

namespace doticu_skylib { namespace Virtual {

    using Stack_ID_t        = u32;
    using Raw_Handle_t      = u64;

    class Type_e;

    class Arguments_i;
    class Arguments_t;
    class Array_t;
    class Callback_i;
    class Callback_t;
    class Class_t;
    class Handle_t;
    class Handle_Policy_t;
    class Machine_t;
    class Object_t;
    class Object_Policy_t;
    class Utils_t;
    class Variable_t;

    template <typename T>
    class Variable_tt;

}}
