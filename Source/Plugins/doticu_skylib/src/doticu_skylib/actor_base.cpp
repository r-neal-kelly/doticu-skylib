/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    Vector_t<Actor_Base_t*> Actor_Base_t::Actor_Bases()
    {
        auto& actor_bases = Game_t::Data()->npcs;

        Vector_t<Actor_Base_t*> results;
        results.reserve(actor_bases.count);

        for (Index_t idx = 0, end = actor_bases.count; idx < end; idx += 1) {
            Actor_Base_t* actor_base = reinterpret_cast<Actor_Base_t*>(actor_bases.entries[idx]);
            if (actor_base) {
                results.push_back(actor_base);
            }
        }

        return results;
    }

    void Actor_Base_t::Log_Actor_Bases()
    {
        #define TAB "    "

        Vector_t<Actor_Base_t*> actor_bases = Actor_Bases();
        _MESSAGE("Log_Actor_Bases {");
        for (size_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
            Actor_Base_t* actor_base = actor_bases[idx];
            _MESSAGE(TAB "index: %6zu, actor_base: %8.8X %s", idx, actor_base->form_id, actor_base->Name());
        }
        _MESSAGE("}");

        #undef TAB
    }

    Sex_e Actor_Base_t::Sex()
    {
        return Is_Female() ? Sex_e::FEMALE : Sex_e::MALE;
    }

    Race_t* Actor_Base_t::Race()
    {
        return race;
    }

}
