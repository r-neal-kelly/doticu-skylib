/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_description.h"
#include "doticu_skylib/component_equip_slot.h"
#include "doticu_skylib/component_menu_display.h"
#include "doticu_skylib/enum_magic_cast_type.h"
#include "doticu_skylib/enum_magic_delivery_type.h"
#include "doticu_skylib/enum_magic_type.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/enum_spell_flags.h"
#include "doticu_skylib/magic_base.h"

namespace doticu_skylib {

    class Perk_t;

    class Spell_t :             // SpellItem
        public Magic_Base_t,    // 00
        public Equip_Slot_c,    // 90
        public Menu_Display_c,  // A0
        public Description_c    // B0
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::SPELL,
        };

        static constexpr const char* SCRIPT_NAME = "Spell";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E10E50, // 513849
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Spell_t(); // 0

    public:
        s32                     cost_override;          // C0
        Spell_Flags_e           spell_flags;            // C4
        Magic_Type_e            magic_type;             // C8
        Float_t                 charge_time;            // CC
        Magic_Cast_Type_e       magic_cast_type;        // D0
        u8                      pad_D1;                 // D1
        u16                     pad_D2;                 // D2
        Magic_Delivery_Type_e   magic_delivery_type;    // D4
        Float_t                 cast_duration;          // D8
        Float_t                 range;                  // DC
        maybe<Perk_t*>          half_cost_perk;         // E0

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Spell_t) == 0xE8);

}
