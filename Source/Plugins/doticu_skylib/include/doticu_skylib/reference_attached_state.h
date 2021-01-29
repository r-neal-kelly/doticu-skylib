/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class NI_3D_t;

    class Reference_Attached_State_t // LoadedState, LOADED_REF_DATA
    {
    public:
        Byte_t          unk_00[0x18];           // 00
        void*           water_type;             // 18
        Float_t         water_height;           // 20
        Float_t         cached_radius;          // 24
        u16             attached_state_flags;   // 28
        s16             underwater_count;       // 2A
        u32             pad_2C;                 // 2C
        Byte_t          unk_30[0x38];           // 30
        maybe<NI_3D_t*> ni_3d;                  // 68
        void*           unk_70;                 // 70
    };
    STATIC_ASSERT(sizeof(Reference_Attached_State_t) == 0x78);

}
