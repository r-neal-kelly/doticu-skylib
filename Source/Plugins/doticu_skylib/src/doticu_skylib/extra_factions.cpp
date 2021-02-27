/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_factions.h"

namespace doticu_skylib {

    some<Extra_Factions_t*> Extra_Factions_t::Create()
    {
        some<Extra_Factions_t*> x_factions = Extra_Data_t::Create<Extra_Factions_t>();

        x_factions->factions_and_ranks = Factions_And_Ranks_t(2);
        x_factions->crime_faction = none<Faction_t*>();
        x_factions->unk_30 = false;
        x_factions->pad_31 = 0;
        x_factions->pad_32 = 0;
        x_factions->pad_34 = 0;

        return x_factions;
    }

    some<Extra_Factions_t*> Extra_Factions_t::Create(some<Faction_t*> faction, some<Raw_Faction_Rank_t> rank)
    {
        some<Extra_Factions_t*> x_factions = Create();
        
        x_factions->Faction_Rank(faction, rank);

        return x_factions;
    }

    some<Extra_Factions_t*> Extra_Factions_t::Create(maybe<Faction_t*> crime_faction)
    {
        some<Extra_Factions_t*> x_factions = Create();

        x_factions->Crime_Faction(crime_faction);

        return x_factions;
    }

    void Extra_Factions_t::Destroy(some<Extra_Factions_t*> x_factions)
    {
        SKYLIB_ASSERT_SOME(x_factions);

        Extra_Data_t::Destroy<Extra_Factions_t>(x_factions);
    }

    maybe<Raw_Faction_Rank_t> Extra_Factions_t::Faction_Rank(some<Faction_t*> faction)
    {
        SKYLIB_ASSERT(faction);

        return this->factions_and_ranks.Faction_Rank(faction);
    }

    void Extra_Factions_t::Faction_Rank(some<Faction_t*> faction, some<Raw_Faction_Rank_t> rank)
    {
        SKYLIB_ASSERT(faction);

        this->factions_and_ranks.Faction_Rank(faction, rank);
    }

    maybe<Faction_t*> Extra_Factions_t::Crime_Faction()
    {
        return this->crime_faction;
    }

    void Extra_Factions_t::Crime_Faction(maybe<Faction_t*> crime_faction)
    {
        this->crime_faction = crime_faction;
    }

}
