/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/faction.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"

namespace doticu_skylib {

    size_t Faction_t::Faction_Count()
    {
        return Game_t::Self()->Factions().count;
    }

    Vector_t<Faction_t*> Faction_t::Factions()
    {
        Vector_t<Faction_t*> results;
        Factions(results);
        return results;
    }

    void Faction_t::Factions(Vector_t<Faction_t*>& results)
    {
        auto& factions = Game_t::Self()->Factions();
        results.reserve(factions.count);

        for (Index_t idx = 0, end = factions.count; idx < end; idx += 1) {
            Faction_t* faction = factions.entries[idx];
            if (faction && faction->Is_Valid()) {
                results.push_back(faction);
            }
        }
    }

    String_t Faction_t::Any_Name()
    {
        const char* name = Name();
        if (name && name[0]) {
            return name;
        } else {
            String_t editor_id = Editor_ID();
            if (editor_id.data && editor_id.data[0]) {
                return editor_id;
            } else {
                return Form_ID_String();
            }
        }
    }

    String_t Faction_t::Editor_ID()
    {
        Mod_t* highest_mod = Get_Highest_Mod();
        if (highest_mod) {
            return highest_mod->Editor_ID("FACT", form_id);
        } else {
            return "";
        }
    }

    void Faction_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Faction_t::Log");
        SKYLIB_LOG(indent + "{");

        if (Is_Valid()) {
            const char* name = Name();
            if (name && name[0]) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "name: %s", name);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "name: (none)");
            }

            String_t editor_id = Editor_ID();
            if (editor_id.data && editor_id.data[0]) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "editor_id: %s", editor_id);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "editor_id: (none)");
            }

            SKYLIB_LOG(indent + SKYLIB_TAB + "form_id: %s", Form_ID_String());
        }

        SKYLIB_LOG(indent + "}");
    }

}
