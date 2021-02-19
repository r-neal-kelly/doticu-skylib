/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Spells_c :        // TESSpellList
        public Form_Data_c  // 00
    {
    public:
        virtual ~Spells_c(); // 0

    public:
        void* unk_08; // 08
    };
    STATIC_ASSERT(sizeof(Spells_c) == 0x10);

}
