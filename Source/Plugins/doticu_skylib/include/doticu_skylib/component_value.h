/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Value_c : public Form_Data_c // TESValueForm
    {
    public:
        virtual ~Value_c(); // 0

        s32 value;  // 08
        u32 pad_0C; // 0C
    };
    STATIC_ASSERT(sizeof(Value_c) == 0x10);

}
