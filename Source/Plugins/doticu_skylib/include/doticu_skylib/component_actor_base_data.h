/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/component_form_data.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum_actor_base_flags.h"
#include "doticu_skylib/enum_actor_base_template_flags.h"
#include "doticu_skylib/enum_vitality.h"
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
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E15430, // 513939
            };
            using Enum_t::Enum_t;
        };

        class Form_Change_Flags_e :
            public Enum_t<u32>
        {
        public:
            enum enum_type : value_type
            {
                ACTOR_BASE_DATA = static_cast<value_type>(1 << 1),
                ATTRIBUTES      = static_cast<value_type>(1 << 2),
                FACTIONS        = static_cast<value_type>(1 << 6),
                GENDER          = static_cast<value_type>(1 << 24),
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Actor_Base_Data_c(); // 0

    public:
        Actor_Base_Flags_e          actor_base_flags;           // 08
        s16                         magicka_offset;             // 0C
        s16                         stamina_offset;             // 0E
        u16                         level;                      // 10
        u16                         min_level_calc;             // 12
        u16                         max_level_calc;             // 14
        u16                         speed_multiplier;           // 16
        u16                         base_disposition;           // 18
        Actor_Base_Template_Flags_e actor_base_template_flags;  // 1A
        s16                         health_offset;              // 1C
        s16                         bleedout_override;          // 1E
        maybe<Leveled_Item_t*>      death_leveled_item;         // 20
        maybe<Voice_Type_t*>        voice_type;                 // 28
        maybe<Form_t*>              template_form;              // 30 (TPLT, but resolved)
        u32                         unk_38;                     // 38
        u32                         unk_3C;                     // 3C
        Factions_And_Ranks_t        factions_and_ranks;         // 40

    public:
        Bool_t  Is_Male();
        Bool_t  Is_Female();
        Bool_t  Is_Unique();
        Bool_t  Is_Generic();
        Bool_t  Is_Ghost();

        Bool_t  Does_Respawn();

        Bool_t  Is_Mortal();
        void    Is_Mortal(Bool_t value, Bool_t do_save);
        Bool_t  Is_Protected();
        void    Is_Protected(Bool_t value, Bool_t do_save);
        Bool_t  Is_Essential();
        void    Is_Essential(Bool_t value, Bool_t do_save);
        Bool_t  Is_Invulnerable();
        void    Is_Invulnerable(Bool_t value, Bool_t do_save);

    public:
        maybe<Raw_Faction_Rank_t>       Faction_Rank(some<Faction_t*> faction);
        void                            Faction_Rank(some<Faction_t*> faction, some<Raw_Faction_Rank_t> rank);
        Vector_t<Faction_And_Rank_t>    Factions_And_Ranks(Bool_t remove_negatives = true);
        void                            Factions_And_Ranks(Vector_t<Faction_And_Rank_t>& results, Bool_t remove_negatives = true);

        some<Vitality_e>                Vitality();
        void                            Vitality(some<Vitality_e> vitality, Bool_t do_save);

        maybe<Voice_Type_t*>            Voice_Type();
        void                            Voice_Type(maybe<Voice_Type_t*> voice_type);

    public:
        void    Log(std::string indent = "");
        void    Log_Factions_And_Ranks(std::string indent = "");
        void    Log_Template_Form(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Actor_Base_Data_c) == 0x58);

}
