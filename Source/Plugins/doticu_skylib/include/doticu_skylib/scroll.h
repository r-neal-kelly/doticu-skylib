/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_grab_sounds.h"
#include "doticu_skylib/component_model_alternates.h"
#include "doticu_skylib/component_value.h"
#include "doticu_skylib/component_weight.h"
#include "doticu_skylib/spell.h"

namespace doticu_skylib {

    class Scroll_t :                // ScrollItem
        public Spell_t,             // 000
        public Model_Alternates_c,  // 0E8
        public Destructible_c,      // 120
        public Grab_Sounds_c,       // 130
        public Weight_c,            // 148
        public Value_c              // 158
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::SCROLL,
        };

        static constexpr const char* SCRIPT_NAME = "Scroll";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E11ED0, // 684635
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Scroll_t(); // 0
    };
    STATIC_ASSERT(sizeof(Scroll_t) == 0x168);

}
