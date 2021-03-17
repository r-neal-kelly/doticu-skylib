/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_attack_damage.h"
#include "doticu_skylib/component_block_bash.h"
#include "doticu_skylib/component_description.h"
#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_enchantable.h"
#include "doticu_skylib/component_equip_slot.h"
#include "doticu_skylib/component_grab_sounds.h"
#include "doticu_skylib/component_icon.h"
#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_message_icon.h"
#include "doticu_skylib/component_model_alternates.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_preloadable.h"
#include "doticu_skylib/component_value.h"
#include "doticu_skylib/component_weight.h"

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Weapon_t :                // TESObjectWEAP
        public Bound_Object_t,      // 000
        public Name_c,              // 030
        public Model_Alternates_c,  // 040
        public Icon_c,              // 078
        public Enchantable_c,       // 088
        public Value_c,             // 0A0
        public Weight_c,            // 0B0
        public Attack_Damage_c,     // 0C0
        public Destructible_c,      // 0D0
        public Equip_Slot_c,        // 0E0
        public Preloadable_c,       // 0F0
        public Message_Icon_c,      // 0F8
        public Grab_Sounds_c,       // 110
        public Block_Bash_c,        // 128
        public Keywords_c,          // 140
        public Description_c        // 158
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::WEAPON,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E14AF8, // 513916
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Weapon_t(); // 0

    public:
        Byte_t data[0xB8]; // 168
    };
    STATIC_ASSERT(sizeof(Weapon_t) == 0x220);

}
