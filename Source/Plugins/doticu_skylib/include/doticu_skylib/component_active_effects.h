/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Active_Effects_c : public Form_Data_c // TESSpellList
    {
    public:
        virtual ~Active_Effects_c(); // 0

        void* active_effects; // 8
    };
    STATIC_ASSERT(sizeof(Active_Effects_c) == 0x10);

}
