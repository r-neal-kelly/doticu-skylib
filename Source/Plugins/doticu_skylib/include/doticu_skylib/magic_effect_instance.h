/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Magic_Effect_t;

    class Magic_Effect_Instance_t // EffectItem
    {
    public:
        Float_t                 magnitude;  // 00
        u32                     area;       // 04
        u32                     duration;   // 08
        u32                     pad_0C;     // 0C
        maybe<Magic_Effect_t*>  base;       // 10
        Float_t                 cost;       // 18
        u32                     pad_1C;     // 1C
        void*                   conditions; // 20
    };
    STATIC_ASSERT(sizeof(Magic_Effect_Instance_t) == 0x28);

}
