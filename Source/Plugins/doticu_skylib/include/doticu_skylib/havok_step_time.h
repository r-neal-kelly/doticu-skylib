/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class alignas(0x10) Havok_Step_Time_t // hkStepInfo
    {
    public:
        Float_t start_time;             // 00
        Float_t stop_time;              // 04
        Float_t delta_time;             // 08
        Float_t inverted_delta_time;    // 0C
    };
    STATIC_ASSERT(sizeof(Havok_Step_Time_t) == 0x10);

}
