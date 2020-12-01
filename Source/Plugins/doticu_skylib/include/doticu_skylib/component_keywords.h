/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Keywords_c : public Form_Data_c
    {
    public:
        virtual ~Keywords_c(); // 0

        void*   keywords;       // 08
        u32     keyword_count;  // 10
        u32     pad_14;         // 14
    };
    STATIC_ASSERT(sizeof(Keywords_c) == 0x18);

}
