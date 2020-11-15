/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/leveled_actor_base.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    Vector_t<Leveled_Actor_Base_t*> Leveled_Actor_Base_t::Leveled_Actor_Bases()
    {
        auto& leveled_actor_bases = Game_t::Data()->arrLVLN;

        Vector_t<Leveled_Actor_Base_t*> results;
        results.reserve(leveled_actor_bases.count);

        for (Index_t idx = 0, end = leveled_actor_bases.count; idx < end; idx += 1) {
            Leveled_Actor_Base_t* leveled_actor_base =
                reinterpret_cast<Leveled_Actor_Base_t*>(leveled_actor_bases.entries[idx]);
            if (leveled_actor_base) {
                results.push_back(leveled_actor_base);
            }
        }

        return results;
    }

    void Leveled_Actor_Base_t::Log_Leveled_Actor_Bases()
    {
        #define TAB "    "

        Vector_t<Leveled_Actor_Base_t*> leveled_actor_bases = Leveled_Actor_Bases();
        _MESSAGE("Log_Leveled_Actor_Bases {");
        for (size_t idx = 0, end = leveled_actor_bases.size(); idx < end; idx += 1) {
            Leveled_Actor_Base_t* leveled_actor_base = leveled_actor_bases[idx];
            _MESSAGE(TAB "index: %6zu, actor_base: %8.8X", idx, leveled_actor_base->form_id);
        }
        _MESSAGE("}");

        #undef TAB
    }

}
