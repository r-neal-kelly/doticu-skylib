/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_equip_slot.h"
#include "doticu_skylib/component_grab_sounds.h"
#include "doticu_skylib/component_icon.h"
#include "doticu_skylib/component_model_alternates.h"
#include "doticu_skylib/component_value.h"
#include "doticu_skylib/component_weight.h"
#include "doticu_skylib/enum_ingredient_flags.h"
#include "doticu_skylib/magic_base.h"

namespace doticu_skylib {

    class Ingredient_t :            // IngredientItem
        public Magic_Base_t,        // 000
        public Model_Alternates_c,  // 090
        public Icon_c,              // 0C8
        public Weight_c,            // 0D8
        public Equip_Slot_c,        // 0E8
        public Destructible_c,      // 0F8
        public Grab_Sounds_c,       // 108
        public Value_c              // 120
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::INGREDIENT,
        };

        static constexpr const char* SCRIPT_NAME = "Ingredient";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E118C8, // 513879
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Ingredient_t(); // 0

    public:
        s32                 cost_override;      // 130
        Ingredient_Flags_e  ingredient_flags;   // 134
        u16                 unk_138;            // 138
        u16                 player_use_count;   // 13A
        u32                 pad_13C;            // 13C
    };
    STATIC_ASSERT(sizeof(Ingredient_t) == 0x140);

}
