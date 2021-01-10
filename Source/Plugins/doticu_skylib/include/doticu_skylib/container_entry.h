/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Bound_Object_t;
    class Container_Entry_Extra_t;

    class Container_Entry_t
    {
    public:
        s32                         count;  // 00
        u32                         pad_04; // 04
        Bound_Object_t*             object; // 08
        Container_Entry_Extra_t*    extra;  // 10 (COED - Container Object Extra Data)
    };
    STATIC_ASSERT(sizeof(Container_Entry_t) == 0x18);

}
