/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"
#include "doticu_skylib/race.h"

namespace doticu_skylib {

    size_t Race_t::Race_Count()
    {
        return Game_t::Self()->Races().count;
    }

    Vector_t<Race_t*> Race_t::Races()
    {
        auto& races = Game_t::Self()->Races();

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
        auto& races = Game_t::Self()->Races();

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

    String_t Race_t::Any_Name()
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
