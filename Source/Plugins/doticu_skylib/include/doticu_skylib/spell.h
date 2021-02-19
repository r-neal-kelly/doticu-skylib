/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_magic_cast_type.h"
#include "doticu_skylib/enum_magic_delivery.h"
#include "doticu_skylib/enum_magic_type.h"
#include "doticu_skylib/enum_spell_flags.h"

#include "doticu_skylib/component_description.h"
#include "doticu_skylib/component_equip_slot.h"
#include "doticu_skylib/component_menu_display.h"

#include "doticu_skylib/magic_base.h"
#include "doticu_skylib/enum_script_type.h"

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

    public:
        virtual ~Spell_t(); // 0

    public:
        s32                 cost_override;      // C0
        Spell_Flags_e       spell_flags;        // C4
        Magic_Type_e        magic_type;         // C8
        Float_t             charge_time;        // CC
        Magic_Cast_Type_e   magic_cast_type;    // D0
        Magic_Delivery_e    magic_delivery;     // D4
        Float_t             cast_duration;      // D8
        Float_t             range;              // DC
        maybe<Perk_t*>      cast_perk;          // E0
    };
    STATIC_ASSERT(sizeof(Spell_t) == 0xE8);

}
