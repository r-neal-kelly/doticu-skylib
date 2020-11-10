/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PapyrusArgs.h"
#include "skse64/PapyrusVM.h"

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib { namespace Papyrus {

    typedef VMClassRegistry     Registry_t;
    typedef IObjectHandlePolicy Policy_t;
    typedef u32                 Stack_ID_t;

    template <typename T> using Vector_t = VMResultArray<T>;

}}
