/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/component_attack_data.h"
#include "doticu_skylib/component_biped_object.h"
#include "doticu_skylib/component_description.h"
#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_model.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_skin.h"
#include "doticu_skylib/component_spells.h"
#include "doticu_skylib/enum_biped_object_type.h"
#include "doticu_skylib/enum_race_flags.h"
#include "doticu_skylib/enum_race_size.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/enum_sex.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/ni_point.h"
#include "doticu_skylib/race_skill_bonus.h"

namespace doticu_skylib {

    class Voice_Type_t;

    class Race_t :              // TESRace
        public Form_t,          // 000
        public Name_c,          // 020
        public Description_c,   // 030
        public Spells_c,        // 040
        public Skin_c,          // 050
        public Biped_Object_c,  // 060
        public Keywords_c,      // 070
        public Attack_Data_c    // 088
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::RACE,
        };

        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E15AA0, // 513954
            };
            using Enum_t::Enum_t;
        };

    public:
        static size_t                   Race_Count();
        static Vector_t<Race_t*>        Races();
        static Vector_t<const char*>    Race_Editor_IDs();
        static void                     Log_Races();

    public:
        virtual ~Race_t(); // 0

    public:
        Model_c                 skeleton_models[Sex_e::_TOTAL_];    // 098
        Race_Skill_Bonus_t      skill_bonuses[7];                   // 0E8
        u16                     pad_0F6;                            // 0F6
        Float_t                 heights[Sex_e::_TOTAL_];            // 0F8
        Float_t                 weights[Sex_e::_TOTAL_];            // 100
        Race_Flags_1_e          race_flags_1;                       // 108
        Float_t                 starting_health;                    // 10C
        Float_t                 starting_magicka;                   // 110
        Float_t                 starting_stamina;                   // 114
        Float_t                 base_carry_weight;                  // 118
        Float_t                 base_mass;                          // 11C
        Float_t                 acceleration;                       // 120
        Float_t                 deceleration;                       // 124
        Race_Size_e             race_size;                          // 128
        Biped_Object_Type_e     head_object_type;                   // 12C
        Biped_Object_Type_e     hair_object_type;                   // 130
        Float_t                 injured_health_percent;             // 134
        Biped_Object_Type_e     shield_object_type;                 // 138
        Float_t                 health_regen;                       // 13C
        Float_t                 magicka_regen;                      // 140
        Float_t                 stamina_regen;                      // 144
        Float_t                 unarmed_damage;                     // 148
        Float_t                 unarmed_reach;                      // 14C
        Biped_Object_Type_e     body_object_type;                   // 150
        Float_t                 aim_angle_tolerance;                // 154
        Float_t                 flight_radius;                      // 158
        Float_t                 angle_acceleration;                 // 15C
        Float_t                 angle_tolerance;                    // 160
        Race_Flags_2_e          race_flags_2;                       // 164
        NI_Point_3_t            mount_offset;                       // 168
        NI_Point_3_t            dismount_offset;                    // 174
        NI_Point_3_t            mount_camera_offset;                // 180

        Byte_t                  data_18C[0xCC];                     // 18C

        maybe<Voice_Type_t*>    voice_types[Sex_e::_TOTAL_];        // 258

        Byte_t                  data_268[0x250];                    // 268

    public:
        String_t Any_Name();

        Bool_t Can_Talk_To_Player();
    };
    STATIC_ASSERT(sizeof(Race_t) == 0x4B8);

}
