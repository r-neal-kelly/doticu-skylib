/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_factions.h"

namespace doticu_skylib {

    some<Extra_Factions_t*> Extra_Factions_t::Create(maybe<Faction_t*> crime_faction)
    {
        some<Extra_Factions_t*> x_factions = Extra_Data_t::Create<Extra_Factions_t>();

        x_factions->factions_and_ranks = Array_t<Faction_And_Rank_t>(2);
        x_factions->crime_faction = crime_faction;
        x_factions->unk_30 = false;
        x_factions->pad_31 = 0;
        x_factions->pad_32 = 0;
        x_factions->pad_34 = 0;

        return x_factions;
    }

    void Extra_Factions_t::Destroy(some<Extra_Factions_t*> x_factions)
    {
        SKYLIB_ASSERT_SOME(x_factions);

        Extra_Data_t::Destroy<Extra_Factions_t>(x_factions);
    }

}
