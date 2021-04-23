/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_form_data.h"
#include "doticu_skylib/enum_magic_cast_type.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Enchantment_t;

    class Enchantable_c :   // TESEnchantableForm
        public Form_Data_c  // 00
    {
    public:
        virtual ~Enchantable_c(); // 0

    public:
        maybe<Enchantment_t*>   enchantment;            // 08
        Magic_Cast_Type_e       enchantment_cast_type;  // 10
        u8                      pad_11;                 // 11
        u16                     enchantment_amount;     // 12 (EAMT)
        u32                     pad_14;                 // 14
    };
    STATIC_ASSERT(sizeof(Enchantable_c) == 0x18);

}
