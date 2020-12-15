/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_reaction.h"

#include "doticu_skylib/form.h"

namespace doticu_skylib {

    class Faction_t :
        public Form_t,
        public Name_c,
        public Reaction_c
    {
    public:
        enum
        {
            FORM_TYPE   = Form_Type_e::FACTION,
            kTypeID     = FORM_TYPE,
        };

    public:
        static size_t               Faction_Count();
        static Vector_t<Faction_t*> Factions();
        static void                 Factions(Vector_t<Faction_t*>& results);

    public:
        virtual ~Faction_t(); // 00

    public:
        String_t    Any_Name();
        String_t    Editor_ID();

        void        Log(std::string indent = "");
    };

}
