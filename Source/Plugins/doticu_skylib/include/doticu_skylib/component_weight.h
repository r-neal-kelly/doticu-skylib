/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Weight_c : public Form_Data_c // TESWeightForm
    {
    public:
        virtual ~Weight_c(); // 0

        Float_t weight; // 08
        u32     pad_0C; // 0C
    };
    STATIC_ASSERT(sizeof(Weight_c) == 0x10);

}
