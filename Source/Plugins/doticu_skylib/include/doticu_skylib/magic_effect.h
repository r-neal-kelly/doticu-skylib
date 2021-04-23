/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_menu_display.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum_actor_value_type.h"
#include "doticu_skylib/enum_magic_archetype.h"
#include "doticu_skylib/enum_magic_cast_type.h"
#include "doticu_skylib/enum_magic_delivery_type.h"
#include "doticu_skylib/enum_magic_effect_flags.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/enum_sound_level.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Art_Object_t;         // BGSArtObject
    class Dual_Cast_Data_t;     // BGSDualCastData
    class Effect_Shader_t;
    class Explosion_t;          // BGSExplosion
    class Image_Adapter_t;      // TESImageSpaceModifier
    class Impact_Data_Set_t;    // BGSImpactDataSet
    class Light_t;
    class Perk_t;
    class Projectile_t;
    class Reference_Effect_t;   // BGSReferenceEffect
    class Spell_t;

    class Magic_Effect_t :      // EffectSetting
        public Form_t,          // 00
        public Name_c,          // 20
        public Menu_Display_c,  // 30
        public Keywords_c       // 40
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::MAGIC_EFFECT,
        };

        static constexpr const char* SCRIPT_NAME = "MagicEffect";

    public:
        virtual ~Magic_Effect_t(); // 0

    public:
        void*                           filter_validation_function; // 058
        void*                           filter_validation_item;     // 060
        Magic_Effect_Flags_e            magic_effect_flags;         // 068
        Float_t                         base_cost;                  // 06C
        maybe<Form_t*>                  associated_form;            // 070
        Actor_Value_Type_e              associated_skill;           // 078
        Actor_Value_Type_e              resist_variable;            // 07C
        s16                             counter_effect_count;       // 080
        u16                             pad_082;                    // 082
        u32                             pad_084;                    // 084
        maybe<Light_t*>                 light;                      // 088
        Float_t                         taper_weight;               // 090
        u32                             pad_094;                    // 094
        maybe<Effect_Shader_t*>         effect_shader;              // 098
        maybe<Effect_Shader_t*>         enchant_shader;             // 0A0
        s32                             minimum_skill;              // 0A8
        s32                             spellmaking_area;           // 0AC
        Float_t                         spellmaking_charge_time;    // 0B0
        Float_t                         taper_curve;                // 0B4
        Float_t                         taper_duration;             // 0B8
        Float_t                         second_actor_value_weight;  // 0BC
        Magic_Archetype_e               archetype;                  // 0C0
        Actor_Value_Type_e              primary_actor_value;        // 0C4
        maybe<Projectile_t*>            projectile;                 // 0C8
        maybe<Explosion_t*>             explosion;                  // 0D0
        Magic_Cast_Type_e               magic_cast_type;            // 0D8
        u8                              pad_0D9;                    // 0D9
        u16                             pad_0DA;                    // 0DA
        Magic_Delivery_Type_e           magic_delivery_type;        // 0DC
        Actor_Value_Type_e              secondary_actor_value;      // 0E0
        u32                             pad_0E4;                    // 0E4
        maybe<Art_Object_t*>            cast_art_object;            // 0E8
        maybe<Art_Object_t*>            hit_art_object;             // 0F0
        maybe<Impact_Data_Set_t*>       impact_data_set;            // 0F8
        Float_t                         skill_Usage_mult;           // 100
        u32                             pad_104;                    // 104
        maybe<Dual_Cast_Data_t*>        dual_cast_data;             // 108
        Float_t                         dual_cast_scale;            // 110
        u32                             pad_114;                    // 114
        maybe<Art_Object_t*>            enchant_art_object;         // 118
        maybe<Reference_Effect_t*>      hit_reference_effect;       // 120
        maybe<Reference_Effect_t*>      enchant_reference_effect;   // 128
        maybe<Spell_t*>                 equip_ability;              // 130
        maybe<Image_Adapter_t*>         image_adapter;              // 138
        maybe<Perk_t*>                  perk;                       // 140
        Sound_Level_e                   cast_sound_level;           // 148
        u8                              pad_149;                    // 149
        u16                             pad_14A;                    // 14A
        Float_t                         ai_score;                   // 14C
        Float_t                         ai_delay_timer;             // 150
        u32                             pad_154;                    // 154
        List_t<maybe<Magic_Effect_t*>>  counter_effects;            // 158
        Array_t<void*>                  sounds;                     // 168
        String_t                        description;                // 180
        s32                             loaded_count;               // 188
        s32                             associated_loaded_count;    // 18C
        void*                           conditions;                 // 190
    };
    STATIC_ASSERT(sizeof(Magic_Effect_t) == 0x198);

}
