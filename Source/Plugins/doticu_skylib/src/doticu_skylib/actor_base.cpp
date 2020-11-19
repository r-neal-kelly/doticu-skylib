/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    size_t Actor_Base_t::Actor_Base_Count()
    {
        return Game_t::Data()->npcs.count;
    }

    Vector_t<Actor_Base_t*> Actor_Base_t::Actor_Bases()
    {
        Vector_t<Actor_Base_t*> results;
        results.reserve(Actor_Base_Count());

        Actor_Bases(results);

        return results;
    }

    void Actor_Base_t::Actor_Bases(Vector_t<Actor_Base_t*>& results)
    {
        auto& actor_bases = Game_t::Data()->npcs;
        for (Index_t idx = 0, end = actor_bases.count; idx < end; idx += 1) {
            Actor_Base_t* actor_base = reinterpret_cast<Actor_Base_t*>(actor_bases.entries[idx]);
            if (actor_base) {
                results.push_back(actor_base);
            }
        }
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

    String_t Actor_Base_t::Any_Name()
    {
        const char* name = Name();
        if (!name || !name[0]) {
            name = Get_Editor_ID();
            if (!name || !name[0]) {
                return Form_ID_String();
            } else {
                return name;
            }
        } else {
            return name;
        }
    }

}
