/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_skills.h"
#include "doticu_skylib/actor_values.h"
#include "doticu_skylib/animated_object.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/component_actor_base_data.h"
#include "doticu_skylib/component_ai.h"
#include "doticu_skylib/component_attack_data.h"
#include "doticu_skylib/component_container.h"
#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_package_override.h"
#include "doticu_skylib/component_perks.h"
#include "doticu_skylib/component_race.h"
#include "doticu_skylib/component_skin.h"
#include "doticu_skylib/component_spells.h"
#include "doticu_skylib/enum_relation.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/enum_sex.h"
#include "doticu_skylib/enum_sound_level.h"
#include "doticu_skylib/faction_and_rank.h"
#include "doticu_skylib/rarity.h"
#include "doticu_skylib/unknown.h"
#include "doticu_skylib/vitality.h"

namespace doticu_skylib {

    class Actor_Class_t; // TESClass
    class Armor_t;
    class Combat_Style_t; // TESCombatStyle
    class Faction_t;
    class Form_List_t;
    class Outfit_t;

    class Actor_Base_t :
        public Animated_Object_t,
        public Actor_Base_Data_c,
        public Container_c,
        public Spells_c,
        public AI_c,
        public Name_c,
        public Actor_Values_t,
        public Destructible_c,
        public Skin_c,
        public Keywords_c,
        public Attack_Data_c,
        public Perks_c,
        public Race_c,
        public Package_Override_c,
        public Event_Sink_t<void*>
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ACTOR_BASE,
        };

        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E14C08, // 513923
            };
            using Enum_t::Enum_t;
        };

        class Form_Change_Flags_e :
            public Enum_t<u32>
        {
        public:
            enum : value_type
            {
                ACTOR_BASE_DATA = static_cast<value_type>(1 << 1),
                ATTRIBUTES      = static_cast<value_type>(1 << 2),
                AI              = static_cast<value_type>(1 << 3),
                SPELLS          = static_cast<value_type>(1 << 4),
                NAME            = static_cast<value_type>(1 << 5),
                FACTIONS        = static_cast<value_type>(1 << 6),
                SKILLS          = static_cast<value_type>(1 << 9),
                CLASS           = static_cast<value_type>(1 << 10),
                FACE            = static_cast<value_type>(1 << 11),
                DEFAULT_OUTFIT  = static_cast<value_type>(1 << 12), // (DOFT)
                SLEEP_OUTFIT    = static_cast<value_type>(1 << 13),
                GENDER          = static_cast<value_type>(1 << 24),
                RACE            = static_cast<value_type>(1 << 25),
            };
            using Enum_t::Enum_t;
        };

    public:
        static size_t                   Actor_Base_Count();
        static Vector_t<Actor_Base_t*>  Actor_Bases();
        static void                     Actor_Bases(Vector_t<Actor_Base_t*>& results);
        static Vector_t<Actor_Base_t*>  Dynamic_Actor_Bases();
        static void                     Dynamic_Actor_Bases(Vector_t<Actor_Base_t*>& results);
        static void                     Log_Actor_Bases();
        static void                     Log_Dynamic_Actor_Bases();

        static void                     Stream_Actor_Bases(Vector_t<some<Actor_Base_t*>>& actor_bases, std::fstream& fstream);

        static Int_t                    Compare_Names(some<Actor_Base_t*>* a, some<Actor_Base_t*>* b);

    public:
        virtual ~Actor_Base_t(); // 0

    public:
        Actor_Skills_t      actor_skills;       // 190
        Actor_Class_t*      actor_class;        // 1C0
        void*               head_data;          // 1C8
        void*               unk_1D0;            // 1D0
        Combat_Style_t*     combat_style;       // 1D8
        u32                 file_offset;        // 1E0
        u32                 pad_1E4;            // 1E4
        Race_t*             extra_race;         // 1E8
        Actor_Base_t*       template_list;      // 1F0
        Float_t             height;             // 1F8
        Float_t             weight;             // 1FC
        void*               sounds;             // 200
        String_t            short_name;         // 208 (SHRT)
        Armor_t*            far_skin;           // 210
        maybe<Outfit_t*>    default_outfit;     // 218 (DOFT)
        maybe<Outfit_t*>    sleep_outfit;       // 220
        Form_List_t*        unk_228;            // 228
        Faction_t*          crime_faction;      // 230
        void*               head_parts;         // 238
        s8                  head_part_count;    // 240
        u8                  unk_241;            // 241
        u8                  unk_242;            // 242
        u8                  unk_243;            // 243
        u8                  unk_244;            // 244
        Sound_Level_e       sound_level;        // 245
        u8_rgba             body_tint;          // 246
        u16                 pad_24A;            // 24A
        u32                 pad_24C;            // 24C
        Array_t<void*>*     relationships;      // 250
        void*               face_data;          // 258
        Array_t<void*>*     tint_layers;        // 260

    public:
        Bool_t                          Has_Template_FF000800();

        Sex_e                           Sex();
        Rarity_e                        Rarity();
        Vitality_e                      Vitality();
        some<Relation_e>                Relation(some<Actor_Base_t*> other);
        void                            Relation(some<Actor_Base_t*> other, some<Relation_e> relation);
        Race_t*                         Race();
        Vector_t<Actor_Base_t*>         Templates();
        void                            Templates(Vector_t<Actor_Base_t*>& results);
        Vector_t<Faction_And_Rank_t>    Factions_And_Ranks(Bool_t remove_negatives = true);
        void                            Factions_And_Ranks(Vector_t<Faction_And_Rank_t>& results, Bool_t remove_negatives = true);
        Vector_t<Keyword_t*>            Keywords(Bool_t include_templates = true);
        void                            Keywords(Vector_t<Keyword_t*>& results, Bool_t include_templates = true);
        Actor_Base_t*                   Highest_Static();
        Actor_Base_t*                   Root_Template();
        Actor_Base_t*                   Root_Base();

        maybe<Outfit_t*>                Default_Outfit();
        void                            Default_Outfit(maybe<Outfit_t*> default_outfit);
        maybe<Outfit_t*>                Sleep_Outfit();
        void                            Sleep_Outfit(maybe<Outfit_t*> sleep_outfit);

        String_t                        Any_Name();

        void                            Log_Factions_And_Ranks(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Actor_Base_t) == 0x268);

}
