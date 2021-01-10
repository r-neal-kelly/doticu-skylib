/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Bound_Object_t;
    class Container_Entry_Extra_t;

    class Leveled_Entry_t // (LVLO)
    {
    public:
        Bound_Object_t*             object; // 00
        u16                         count;  // 08
        u16                         level;  // 0A
        u32                         pad_0C; // 0C
        Container_Entry_Extra_t*    extra;  // 10 (COED)
    };
    STATIC_ASSERT(sizeof(Leveled_Entry_t) == 0x18);

}
