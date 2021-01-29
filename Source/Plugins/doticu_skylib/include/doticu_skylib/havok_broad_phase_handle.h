/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_havok_collidable_flags.h"

#include "doticu_skylib/havok_broad_phase_id.h"

namespace doticu_skylib {

    class Havok_Broad_Phase_Handle_t // hkpTypedBroadPhaseHandle
    {
    public:
        Havok_Broad_Phase_ID_t      id;                 // 0
        s8                          type;               // 4
        s8                          owner_offset;       // 5
        s8                          quality_type;       // 6
        s8                          pad_7;              // 7
        Havok_Collidable_Flags_e    collidable_flags;   // 8
    };
    STATIC_ASSERT(sizeof(Havok_Broad_Phase_Handle_t) == 0xC);

}
