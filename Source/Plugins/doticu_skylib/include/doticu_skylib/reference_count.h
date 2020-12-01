/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Reference_Count_t {
    public:
        virtual ~Reference_Count_t();

        volatile u32    reference_count;    // 08
        u32             pad_0C;             // 0C

        Int_t Reference_Count();
        Int_t Increment_Reference();
        Int_t Decrement_Reference();
    };
    STATIC_ASSERT(sizeof(Reference_Count_t) == 0x10);

}
