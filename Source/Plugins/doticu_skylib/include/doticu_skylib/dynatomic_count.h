/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Dynatomic_Count_t // NiRefObject
    {
    public:
        virtual         ~Dynatomic_Count_t();   // 0
        virtual void    Destroy();              // 1

    public:
        volatile u32    dynatomic_count;    // 08
        u32             pad_0C;             // 0C

    public:
        u32 Dynatomic_Count();
        u32 Increment_Dynatomic();
        u32 Decrement_Dynatomic();
    };
    STATIC_ASSERT(sizeof(Dynatomic_Count_t) == 0x10);

}
