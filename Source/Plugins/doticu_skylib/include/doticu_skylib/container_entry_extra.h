/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Form_t;
    class Global_t;

    class Container_Entry_Extra_t // ContainerItemExtra
    {
    public:
        union Conditional_u
        {
            Global_t*   global;
            s32         rank;   // (faction rank?)
        };
        STATIC_ASSERT(sizeof(Conditional_u) == 0x8);

    public:
        Form_t*         owner;          // 00
        Conditional_u   conditional;    // 08
        Float_t         health;         // 10
        u32             pad_14;         // 14
    };
    STATIC_ASSERT(sizeof(Container_Entry_Extra_t) == 0x18);

}
