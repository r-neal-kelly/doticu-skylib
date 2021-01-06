/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"

#include "doticu_skylib/component_biped_model.h"
#include "doticu_skylib/component_biped_object.h"
#include "doticu_skylib/component_block_bash.h"
#include "doticu_skylib/component_description.h"
#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_enchantable.h"
#include "doticu_skylib/component_equip_slot.h"
#include "doticu_skylib/component_grab_sounds.h"
#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_race.h"
#include "doticu_skylib/component_value.h"
#include "doticu_skylib/component_weight.h"

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/script_type.h"

namespace doticu_skylib {

    class Armor_t :
        public Bound_Object_t,
        public Name_c,
        public Race_c,
        public Enchantable_c,
        public Value_c,
        public Weight_c,
        public Destructible_c,
        public Grab_Sounds_c,
        public Biped_Model_c,
        public Equip_Slot_c,
        public Biped_Object_c,
        public Block_Bash_c,
        public Keywords_c,
        public Description_c
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ARMOR,
        };

    public:
        virtual ~Armor_t(); // 00

        u32             rating;     // 200
        u32             pad_204;    // 204
        Array_t<void*>  addons;     // 208
        Armor_t*        templates;  // 220
    };
    STATIC_ASSERT(sizeof(Armor_t) == 0x228);

}
