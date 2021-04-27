/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

#include "doticu_skylib/collections.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_reactions.h"
#include "doticu_skylib/enum_faction_flags.h"
#include "doticu_skylib/enum_reaction_type.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Actor_Base_t;
    class Form_List_t;
    class Outfit_t;
    class Reference_t;

    class Faction_t :       // TESFaction
        public Form_t,      // 000
        public Name_c,      // 020
        public Reactions_c  // 030
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::FACTION,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI                = 0x01E138A0, // 513906

                SET_REACTION_TYPE   = 0x00355940, // 24012
            };
            using Enum_t::Enum_t;
        };

        class Form_Change_Flags_e :
            public Enum_t<u32>
        {
        public:
            enum enum_type : value_type
            {
                FORM_FLAGS      = static_cast<value_type>(1 << 0),
                FACTION_FLAGS   = static_cast<value_type>(1 << 1),
            };
            using Enum_t::Enum_t;
        };

    public:
        static Vector_t<const char*>    editor_ids;
        static std::mutex               editor_ids_mutex;

    public:
        static void                 Init_Editor_IDs();

        static size_t               Faction_Count();
        static Vector_t<Faction_t*> Factions();
        static void                 Factions(Vector_t<Faction_t*>& results);

        static Int_t                Compare_Editor_Or_Form_IDs(Faction_t** a, Faction_t** b);

    public:
        virtual ~Faction_t(); // 00

    public:
        maybe<Hash_Map_t<maybe<Actor_Base_t*>, u32>*>   actor_base_to_crime_gold;   // 050 (maybe s32)
        Faction_Flags_e                                 faction_flags;              // 058
        u32                                             editor_id_index;            // 05C (pad_05C)
        maybe<Reference_t*>                             jail_marker;                // 060
        maybe<Reference_t*>                             unk_crime_marker;           // 068
        maybe<Reference_t*>                             stolen_container;           // 070
        maybe<Reference_t*>                             possessions_container;      // 078
        maybe<Form_List_t*>                             unk_crime_form_list;        // 080
        maybe<Outfit_t*>                                jail_outfit;                // 088
        Bool_t                                          do_arrest;                  // 090
        Bool_t                                          do_arrest_on_sight;         // 091
        u16                                             murder_gold;                // 092
        u16                                             assault_gold;               // 094
        u16                                             trespass_gold;              // 096
        u16                                             pickpocket_gold;            // 098
        u16                                             pad_09A;                    // 09A
        Float_t                                         steal_gold_mult;            // 09C
        u16                                             escape_gold;                // 0A0
        u16                                             werewolf_gold;              // 0A2
        u32                                             pad_0A4;                    // 0A4
        Byte_t                                          unk_060[0x58];              // 0A8

    public:
        String_t    Any_Name();
        const char* Editor_ID();
        String_t    Editor_Or_Form_ID();

        void        Reaction_Type(some<Faction_t*> other, some<Reaction_Type_e> reaction_type);

    public:
        void        Log(std::string indent = "");
        void        Log_Basic(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Faction_t) == 0x100);

}
