/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Havok_Broad_Phase_Handle_t // hkpBroadPhaseHandle
    {
    public:
        s32 broad_phase_id; // 0
    };
    STATIC_ASSERT(sizeof(Havok_Broad_Phase_Handle_t) == 0x4);

}
