/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Actor_AI_Cached_Value_t // CachedValueData
    {
    public:
        Bool_t  is_dirty;   // 0
        u8      pad_1;      // 1
        u16     pad_2;      // 2
        Float_t value;      // 4
    };
    STATIC_ASSERT(sizeof(Actor_AI_Cached_Value_t) == 0x8);

}
