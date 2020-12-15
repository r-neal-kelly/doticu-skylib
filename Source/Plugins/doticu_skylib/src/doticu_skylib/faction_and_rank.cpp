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
