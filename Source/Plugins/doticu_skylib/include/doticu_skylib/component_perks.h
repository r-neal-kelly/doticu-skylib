/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Perks_c : public Form_Data_c // BGSPerkRankArray
    {
    public:
        virtual ~Perks_c(); // 0

        void*   perks;      // 08
        u32     perk_count; // 10
        u32     pad_14;     // 14
    };
    STATIC_ASSERT(sizeof(Perks_c) == 0x18);

}
