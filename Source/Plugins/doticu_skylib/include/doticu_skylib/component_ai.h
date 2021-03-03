/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    // this is a juicy type we need to better define

    class AI_c : public Form_Data_c // TESAIForm
    {
    public:
        virtual ~AI_c(); // 0

    public:
        u8 ai_data[0x20]; // 08
    };
    STATIC_ASSERT(sizeof(AI_c) == 0x28);

}
