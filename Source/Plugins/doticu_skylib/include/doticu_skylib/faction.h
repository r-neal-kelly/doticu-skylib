/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

#include "doticu_skylib/collections.h"
#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/enum_faction_flags.h"

#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_reaction.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/script_type.h"

namespace doticu_skylib {

    class Actor_Base_t;

    class Faction_t :
        public Form_t,
        public Name_c,
        public Reaction_c
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::FACTION,
        };

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

        Hash_Map_t<Actor_Base_t*, u32>* actor_base_to_crime_gold;   // 050
        Faction_Flags_e                 faction_flags;              // 058
        u32                             editor_id_index;            // 05C (pad_05C)
        // ...

    public:
        String_t    Any_Name();
        const char* Editor_ID();
        String_t    Editor_Or_Form_ID();

        void        Log(std::string indent = "");
    };

}
