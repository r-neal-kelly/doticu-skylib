/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/enum_ni_update_flags.h"

namespace doticu_skylib {

    class NI_Update_t // NiUpdateData
    {
    public:
        Float_t             time;           // 0
        NI_Update_Flags_e   update_flags;   // 4

    public:
        NI_Update_t();
    };
    STATIC_ASSERT(sizeof(NI_Update_t) == 0x8);

}
