/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_grab_sounds.h"
#include "doticu_skylib/component_icon.h"
#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_message_icon.h"
#include "doticu_skylib/component_model_alternates.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_value.h"
#include "doticu_skylib/component_weight.h"

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/script_type.h"

namespace doticu_skylib {

    class Misc_t :
        public Bound_Object_t,
        public Name_c,
        public Model_Alternates_c,
        public Icon_c,
        public Value_c,
        public Weight_c,
        public Destructible_c,
        public Message_Icon_c,
        public Grab_Sounds_c,
        public Keywords_c
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::MISC,
        };

    public:
        virtual ~Misc_t(); // 00
    };
    STATIC_ASSERT(sizeof(Misc_t) == 0x100);

}
