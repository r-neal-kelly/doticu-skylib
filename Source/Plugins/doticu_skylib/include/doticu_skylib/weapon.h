/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/bound_object.h"
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
#include "doticu_skylib/enum_actor_value_type.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/enum_sound_level.h"
#include "doticu_skylib/enum_weapon_animation_type.h"
#include "doticu_skylib/enum_weapon_attack_type.h"
#include "doticu_skylib/enum_weapon_critical_flags.h"
#include "doticu_skylib/enum_weapon_flags.h"
#include "doticu_skylib/enum_weapon_hit_type.h"
#include "doticu_skylib/enum_weapon_rumble_type.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Impact_Data_Set_t;    // BGSImpactDataSet
    class Sound_Descriptor_t;   // BGSSoundDescriptorForm
    class Spell_t;
    class Static_t;

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

        static constexpr const char* SCRIPT_NAME = "Weapon";

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
        void*                       range_data;             // 168
        Float_t                     speed;                  // 170
        Float_t                     reach;                  // 174
        Float_t                     min_range;              // 178
        Float_t                     max_range;              // 17C
        Float_t                     animation_attack_mult;  // 180
        Float_t                     unk_184;                // 184
        Float_t                     stagger_value;          // 188
        Weapon_Hit_Type_e           weapon_hit_type;        // 18C
        Actor_Value_Type_e          skill_type;             // 190
        Actor_Value_Type_e          resistance_type;        // 194
        Weapon_Flags_1_e            weapon_flags_1;         // 198
        u8                          base_vats_hit_chance;   // 19A
        Weapon_Attack_Type_e        weapon_attack_type;     // 19B
        u8                          unk_19C;                // 19C
        Weapon_Animation_Type_e     weapon_animation_type;  // 19D
        Weapon_Flags_2_e            weapon_flags_2;         // 19E
        u8                          unk_19F;                // 19F
        Float_t                     critical_percent_mult;  // 1A0
        u32                         pad_1A4;                // 1A4
        maybe<Spell_t*>             critical_effect;        // 1A8
        u16                         critical_damage;        // 1B0
        Weapon_Critical_Flags_e     weapon_critical_flags;  // 1B2
        u8                          pad_1B3;                // 1B3
        u32                         pad_1B4;                // 1B4
        void*                       unk_1B8;                // 1B8
        maybe<Sound_Descriptor_t*>  attack_sound;           // 1C0
        maybe<Sound_Descriptor_t*>  attack_sound_2D;        // 1C8
        maybe<Sound_Descriptor_t*>  attack_loop_sound;      // 1D0
        maybe<Sound_Descriptor_t*>  attack_fail_sound;      // 1D8
        maybe<Sound_Descriptor_t*>  idle_sound;             // 1E0
        maybe<Sound_Descriptor_t*>  equip_sound;            // 1E8
        maybe<Sound_Descriptor_t*>  unequip_sound;          // 1F0
        maybe<Impact_Data_Set_t*>   impact_data_set;        // 1F8
        maybe<Static_t*>            first_person_model;     // 200
        maybe<Weapon_t*>            weapon_template;        // 208
        String_t                    embedded_nif_node;      // 210
        Sound_Level_e               sound_level;            // 218
        u8                          pad_219;                // 219
        u8                          pad_21A;                // 21A
        u8                          pad_21B;                // 21B
        u32                         pad_21C;                // 21C

    public:
        Bool_t  Is_Enchanted() const;

        Bool_t  Is_Sword() const;
        Bool_t  Is_Greatsword() const;
        Bool_t  Is_Waraxe() const;
        Bool_t  Is_Battleaxe() const;
        Bool_t  Is_Mace() const;
        Bool_t  Is_Warhammer() const;
        Bool_t  Is_Dagger() const;
        Bool_t  Is_Staff() const;
        Bool_t  Is_Bow() const;
        Bool_t  Is_Crossbow() const;
        Bool_t  Is_Bow_Or_Crossbow() const;

        Bool_t  Is_Wood_Material() const;
        Bool_t  Is_Iron_Material() const;
        Bool_t  Is_Steel_Material() const;
        Bool_t  Is_Silver_Material() const;
        Bool_t  Is_Imperial_Material() const;
        Bool_t  Is_Nordic_Material() const;
        Bool_t  Is_Draugr_Material() const;
        Bool_t  Is_Draugr_Honed_Material() const;
        Bool_t  Is_Falmer_Material() const;
        Bool_t  Is_Falmer_Honed_Material() const;
        Bool_t  Is_Dwarven_Material() const;
        Bool_t  Is_Orcish_Material() const;
        Bool_t  Is_Elven_Material() const;
        Bool_t  Is_Glass_Material() const;
        Bool_t  Is_Ebony_Material() const;
        Bool_t  Is_Daedric_Material() const;
        Bool_t  Is_Dragonbone_Material() const;
        Bool_t  Is_Stalhrim_Material() const;
        Bool_t  Is_Aetherium_Material() const;

        Bool_t  Is_Daedric_Artifact() const;

    public:
        void    Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Weapon_t) == 0x220);

}
