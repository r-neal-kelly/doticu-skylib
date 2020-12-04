/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Read_Write_Lock_t
    {
    public:
        Read_Write_Lock_t() :
            thread(0), lock(0)
        {
        }

        volatile u32 thread;    // 0
        volatile u32 lock;      // 4
    };

}
