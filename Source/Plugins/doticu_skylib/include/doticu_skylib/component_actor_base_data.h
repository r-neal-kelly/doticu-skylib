/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/component_form_data.h"
#include "doticu_skylib/enum_actor_base_flags.h"
#include "doticu_skylib/enum_actor_base_template_flags.h"
#include "doticu_skylib/faction_and_rank.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Form_t;
    class Leveled_Item_t;
    class Voice_Type_t;

    class Actor_Base_Data_c :   // TESActorBaseData
        public Form_Data_c      // 00
    {
    public:
        virtual ~Actor_Base_Data_c(); // 0

    public:
        Atomic_Enum_t<Actor_Base_Flags_e>           actor_base_flags;           // 08
        s16                                         magicka_offset;             // 0C
        s16                                         stamina_offset;             // 0E
        u16                                         level;                      // 10
        u16                                         min_level_calc;             // 12
        u16                                         max_level_calc;             // 14
        u16                                         speed_multiplier;           // 16
        u16                                         base_disposition;           // 18
        Atomic_Enum_t<Actor_Base_Template_Flags_e>  actor_base_template_flags;  // 1A
        s16                                         health_offset;              // 1C
        s16                                         bleedout_override;          // 1E
        maybe<Leveled_Item_t*>                      death_leveled_item;         // 20
        maybe<Voice_Type_t*>                        voice_type;                 // 28
        Form_t*                                     base_template_form;         // 30
        Form_t**                                    template_forms;             // 38
        Array_t<Faction_And_Rank_t>                 factions_and_ranks;         // 40

    public:
        Bool_t Is_Male();
        Bool_t Is_Female();
        Bool_t Is_Unique();
        Bool_t Is_Generic();
        Bool_t Is_Ghost();
        Bool_t Is_Mortal();
        Bool_t Is_Protected();
        Bool_t Is_Essential();
        Bool_t Is_Invulnerable();
    };
    STATIC_ASSERT(sizeof(Actor_Base_Data_c) == 0x58);

}
