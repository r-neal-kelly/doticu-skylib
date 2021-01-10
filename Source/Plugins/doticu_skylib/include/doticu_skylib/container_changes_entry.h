/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/forward_list.h"

#include "doticu_skylib/extra_list.h"

namespace doticu_skylib {

    class Bound_Object_t;

    class Container_Changes_Entry_t
    {
    public:
        Bound_Object_t*     object;         // 00
        List_t<List_x*>*    xlists;         // 08
        s32                 count_delta;    // 10
        u32                 pad_14;         // 14
    };
    STATIC_ASSERT(sizeof(Container_Changes_Entry_t) == 0x18);

}
