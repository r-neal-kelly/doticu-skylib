/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/faction.h"
#include "doticu_skylib/faction_and_rank.h"

namespace doticu_skylib {

    Bool_t Faction_And_Rank_t::Has_Same_Faction(const Faction_And_Rank_t& a, const Faction_And_Rank_t& b)
    {
        return a.faction == b.faction;
    }

    Int_t Faction_And_Rank_t::Compare_Editor_Or_Form_IDs(Faction_And_Rank_t* a, Faction_And_Rank_t* b)
    {
        if (!a || !a->faction) {
            return Comparator_e::IS_UNORDERED;
        } else if (!b || !b->faction) {
            return Comparator_e::IS_ORDERED;
        } else {
            Comparator_e result = Form_t::Compare_Names(
                a->faction->Editor_Or_Form_ID(),
                b->faction->Editor_Or_Form_ID()
            );
            if (result == Comparator_e::IS_EQUAL) {
                return a->faction->form_id - b->faction->form_id;
            } else {
                return result;
            }
        }
    }

    Bool_t Faction_And_Rank_t::Is_Valid()
    {
        return faction && faction->Is_Valid();
    }

    void Faction_And_Rank_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Faction_And_Rank_t::Log");
        SKYLIB_LOG(indent + "{");

        if (faction && faction->Is_Valid()) {
            faction->Log(indent + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "faction: (none)");
        }
        SKYLIB_LOG(indent + SKYLIB_TAB + "rank: %i", rank);

        SKYLIB_LOG(indent + "}");
    }

}
