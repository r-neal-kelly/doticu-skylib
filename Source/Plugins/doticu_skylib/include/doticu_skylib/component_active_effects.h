/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    // not sure this leads directly to active magic effects or some intermediary. it's confusing if I remember correctly!

    class Active_Magic_Effects_c : public Form_Data_c // TESSpellList
    {
    public:
        virtual ~Active_Magic_Effects_c(); // 0

        void* unk_08; // 8
    };
    STATIC_ASSERT(sizeof(Active_Magic_Effects_c) == 0x10);

}
