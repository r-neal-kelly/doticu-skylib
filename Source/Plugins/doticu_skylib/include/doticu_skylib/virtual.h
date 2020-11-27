/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PapyrusArgs.h"
#include "skse64/PapyrusNativeFunctions.h"
#include "skse64/PapyrusVM.h"

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib { namespace Virtual {

    typedef VMClassRegistry     Registry_t;
    typedef u32                 Stack_ID_t;
    typedef u64                 Raw_Handle_t;

    class Array_t;
    class Callback_i;
    class Class_t;
    class Machine_t;
    class Object_t;
    class Variable_t;

    template <typename T>
    class Array_Variable_t;
    class Bool_Variable_t;
    class Int_Variable_t;
    class String_Variable_t;

}}
