/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_broad_phase_handle.h"
#include "doticu_skylib/havok_collidable_body.h"

namespace doticu_skylib {

    class Havok_Collidable_t :          // hkpCollidable
        public Havok_Collidable_Body_t  // 00
    {
    public:
        s8                          owner_offset;       // 20
        u8                          unk_21;             // 21
        u16                         unk_22;             // 22
        Havok_Broad_Phase_Handle_t  broad_phase_handle; // 24
        Byte_t                      data_30[0x40];      // 30
    };
    STATIC_ASSERT(sizeof(Havok_Collidable_t) == 0x70);

}
