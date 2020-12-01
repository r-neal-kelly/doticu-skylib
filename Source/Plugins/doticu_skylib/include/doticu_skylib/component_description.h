/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Description_c : public Form_Data_c // TESDescription
    {
    public:
        virtual ~Description_c(); // 0

        u32 description_offset;     // 8
        u32 description_text_id;    // C
    };
    STATIC_ASSERT(sizeof(Description_c) == 0x10);

}
