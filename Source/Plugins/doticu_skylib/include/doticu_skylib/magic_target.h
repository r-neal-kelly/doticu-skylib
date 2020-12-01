/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Magic_Target_t
    {
    public:
        virtual ~Magic_Target_t();

        void*   unk_08; // 08
        u8      unk_10; // 10
        u8      pad_11; // 11
        u16     pad_12; // 12
        u32     pad_14; // 14
    };
    STATIC_ASSERT(sizeof(Magic_Target_t) == 0x18);

}
