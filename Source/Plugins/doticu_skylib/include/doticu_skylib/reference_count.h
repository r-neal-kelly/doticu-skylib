/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/dynatomic_count.h"

namespace doticu_skylib {

    class Reference_Count_t : public Dynatomic_Count_t
    {
    public:
        virtual ~Reference_Count_t(); // 0

    public:
        u32 Reference_Count();
        u32 Increment_Reference();
        u32 Decrement_Reference();
    };
    STATIC_ASSERT(sizeof(Reference_Count_t) == 0x10);

}
