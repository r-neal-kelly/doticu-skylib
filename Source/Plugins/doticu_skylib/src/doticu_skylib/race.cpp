/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/race.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    Vector_t<Race_t*> Race_t::Races()
    {
        auto& races = Game_t::Data()->races;

        Vector_t<Race_t*> results;
        results.reserve(races.count);

        for (Index_t idx = 0, end = races.count; idx < end; idx += 1) {
            Race_t* race = reinterpret_cast<Race_t*>(races.entries[idx]);
            if (race) {
                results.push_back(race);
            }
        }

        return results;
    }

    Vector_t<const char*> Race_t::Race_Editor_IDs()
    {
        auto& races = Game_t::Data()->races;

        Vector_t<const char*> results;
        results.reserve(races.count);

        for (Index_t idx = 0, end = races.count; idx < end; idx += 1) {
            Race_t* race = reinterpret_cast<Race_t*>(races.entries[idx]);
            if (race) {
                results.push_back(race->Get_Editor_ID());
            }
        }

        return results;
    }

    void Race_t::Log_Races()
    {
        #define TAB "    "

        Vector_t<Race_t*> races = Races();
        _MESSAGE("Log_Races {");
        for (size_t idx = 0, end = races.size(); idx < end; idx += 1) {
            Race_t* race = races[idx];
            _MESSAGE(TAB "index: %6zu, race: %8.8X %s %s",
                     idx, race->form_id, race->Name(), race->Get_Editor_ID());
        }
        _MESSAGE("}");

        #undef TAB
    }

}
