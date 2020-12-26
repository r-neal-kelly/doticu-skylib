/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Reference_Count_t {
    private:
        volatile u32    reference_count;    // 08
    public:
        u32             pad_0C;             // 0C

        virtual         ~Reference_Count_t();   // 0
        virtual void    Destroy();              // 1

        u32 Reference_Count();
        u32 Increment_Reference();
        u32 Decrement_Reference();
    };
    STATIC_ASSERT(sizeof(Reference_Count_t) == 0x10);

}
