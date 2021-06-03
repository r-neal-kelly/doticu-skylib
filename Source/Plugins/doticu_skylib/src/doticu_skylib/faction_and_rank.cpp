/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/enum_comparator.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/faction_and_rank.h"

namespace doticu_skylib {

    Bool_t Faction_And_Rank_t::Has_Same_Faction(const Faction_And_Rank_t& a, const Faction_And_Rank_t& b)
    {
        return a.faction == b.faction;
    }

    Int_t Faction_And_Rank_t::Compare_Editor_Or_Form_IDs(Faction_And_Rank_t& a, Faction_And_Rank_t& b)
    {
        if (!a.faction) {
            return Comparator_e::IS_UNORDERED;
        } else if (!b.faction) {
            return Comparator_e::IS_ORDERED;
        } else {
            Comparator_e result = Form_t::Compare_Names(
                a.faction->Editor_Or_Form_ID(),
                b.faction->Editor_Or_Form_ID()
            );
            if (result == Comparator_e::IS_EQUAL) {
                return a.faction->form_id - b.faction->form_id;
            } else {
                return result;
            }
        }
    }

    Faction_And_Rank_t::Faction_And_Rank_t(some<Faction_t*> faction, some<Raw_Faction_Rank_t> rank) :
        faction(faction()), rank(rank), pad_09(0), pad_0A(0), pad_0C(0)
    {
        SKYLIB_ASSERT_SOME(this->faction);
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

    maybe<Raw_Faction_Rank_t> Factions_And_Ranks_t::Faction_Rank(some<Faction_t*> faction)
    {
        SKYLIB_ASSERT_SOME(faction);

        for (size_t idx = 0, end = Count(); idx < end; idx += 1) {
            Faction_And_Rank_t& faction_and_rank = At(idx);
            if (faction_and_rank.faction == faction) {
                return faction_and_rank.rank;
            }
        }
        return none<Raw_Faction_Rank_t>();
    }

    void Factions_And_Ranks_t::Faction_Rank(some<Faction_t*> faction, some<Raw_Faction_Rank_t> rank)
    {
        SKYLIB_ASSERT_SOME(faction);

        for (size_t idx = 0, end = Count(); idx < end; idx += 1) {
            Faction_And_Rank_t& faction_and_rank = At(idx);
            if (faction_and_rank.faction == faction) {
                faction_and_rank.rank = rank;
                return;
            }
        }
        Push(Faction_And_Rank_t(faction, rank));
    }

}
