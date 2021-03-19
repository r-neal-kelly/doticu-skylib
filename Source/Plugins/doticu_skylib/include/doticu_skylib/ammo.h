/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/component_description.h"
#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_grab_sounds.h"
#include "doticu_skylib/component_icon.h"
#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_message_icon.h"
#include "doticu_skylib/component_model_alternates.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_value.h"
#include "doticu_skylib/component_weight.h"
#include "doticu_skylib/enum_ammo_flags.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Projectile_t;

    class Ammo_t :                  // TESAmmo
        public Bound_Object_t,      // 000
        public Name_c,              // 030
        public Model_Alternates_c,  // 040
        public Icon_c,              // 078
        public Message_Icon_c,      // 088
        public Value_c,             // 0A0
        public Weight_c,            // 0B0
        public Destructible_c,      // 0C0
        public Grab_Sounds_c,       // 0D0
        public Description_c,       // 0E8
        public Keywords_c           // 0F8
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::AMMO,
        };

        static constexpr const char* SCRIPT_NAME = "Ammo";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E137E8, // 513901
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Ammo_t(); // 00

    public:
        maybe<Projectile_t*>    projectile; // 110
        Ammo_Flags_e            ammo_flags; // 118
        u8                      pad_119;    // 119
        u16                     pad_11A;    // 11A
        Float_t                 damage;     // 11C
        String_t                unk_120;    // 120 (ONAM)
    };
    STATIC_ASSERT(sizeof(Ammo_t) == 0x128);

}
