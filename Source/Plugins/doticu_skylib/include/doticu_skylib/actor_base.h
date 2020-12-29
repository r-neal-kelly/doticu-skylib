/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_active_effects.h"
#include "doticu_skylib/component_actor_base_data.h"
#include "doticu_skylib/component_ai.h"
#include "doticu_skylib/component_attack.h"
#include "doticu_skylib/component_container.h"
#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_package_override.h"
#include "doticu_skylib/component_perks.h"
#include "doticu_skylib/component_race.h"
#include "doticu_skylib/component_skin.h"

#include "doticu_skylib/actor_values.h"
#include "doticu_skylib/animated_object.h"
#include "doticu_skylib/faction_and_rank.h"
#include "doticu_skylib/rarity.h"
#include "doticu_skylib/relation.h"
#include "doticu_skylib/script_type.h"
#include "doticu_skylib/sex.h"
#include "doticu_skylib/unknown.h"
#include "doticu_skylib/vitality.h"

namespace doticu_skylib {

    class Actor_Class_t; // TESClass
    class Combat_Style_t; // TESCombatStyle

    class Actor_Base_t :
        public Animated_Object_t,
        public Actor_Base_Data_c,
        public Container_c,
        public Active_Magic_Effects_c,
        public AI_c,
        public Name_c,
        public Actor_Values_t,
        public Destructible_c,
        public Skin_c,
        public Keywords_c,
        public Attack_c,
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
        virtual ~Actor_Base_t();

        u8              skills[18];     // 190 // 00
        u8              unk_1A2[18];    // 1A2 // 12
        u16             attributes[3];  // 1B4 // 24
        u16             pad_1BA;        // 1BA // 2A
        Float_t         unk_1BC;        // 1BC // 2C
        Actor_Class_t*  actor_class;    // 1C0
        void*           head_data;      // 1C8
        void*           unk_1D0;        // 1D0
        Combat_Style_t* combat_style;   // 1D8
        u32             file_offset;    // 1E0
        u32             pad_1E4;        // 1E4
        Race_t*         extra_race;     // 1E8
        Actor_Base_t*   template_list;  // 1F0
        Float_t         height;         // 1F8
        Float_t         weight;         // 1FC
        // ...

    public:
        Bool_t                          Has_Template_FF000800();

        Sex_e                           Sex();
        Rarity_e                        Rarity();
        Vitality_e                      Vitality();
        Relation_e                      Relation(maybe<Actor_Base_t*> other);
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

        String_t                        Any_Name();

        void                            Log_Factions_And_Ranks(std::string indent = "");
    };
    //STATIC_ASSERT(sizeof(Actor_Base_t) == 0x0);

}
