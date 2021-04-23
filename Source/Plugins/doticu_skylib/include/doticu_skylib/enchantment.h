/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_enchantment_flags.h"
#include "doticu_skylib/enum_magic_cast_type.h"
#include "doticu_skylib/enum_magic_delivery_type.h"
#include "doticu_skylib/enum_magic_type.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/magic_base.h"

namespace doticu_skylib {

    class Form_List_t;

    class Enchantment_t :   // EnchantmentItem
        public Magic_Base_t // 00
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ENCHANTMENT,
        };

        static constexpr const char* SCRIPT_NAME = "Enchantment";

    public:
        virtual ~Enchantment_t(); // 0

    public:
        s32                     cost_override;          // 90
        Enchantment_Flags_e     enchantment_flags;      // 94
        Magic_Cast_Type_e       magic_cast_type;        // 98
        u8                      pad_99;                 // 99
        u16                     pad_9A;                 // 9A
        s32                     charge_override;        // 9C
        Magic_Delivery_Type_e   magic_delivery_type;    // A0
        Magic_Type_e            magic_type;             // A4
        Float_t                 charge_time;            // A8
        u32                     pad_AC;                 // AC
        maybe<Enchantment_t*>   base_enchantment;       // B0
        maybe<Form_List_t*>     worn_restrictions;      // B8

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Enchantment_t) == 0xC0);

}
