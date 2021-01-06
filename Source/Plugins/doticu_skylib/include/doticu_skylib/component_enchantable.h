/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Enchantable_c : public Form_Data_c // TESEnchantableForm
    {
    public:
        virtual ~Enchantable_c(); // 0

        void*   unk_08; // 08
        u16     unk_10; // 10
        u16     unk_12; // 12
        u32     unk_14; // 14
    };
    STATIC_ASSERT(sizeof(Enchantable_c) == 0x18);

}
