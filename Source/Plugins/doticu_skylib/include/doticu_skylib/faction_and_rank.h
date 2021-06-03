/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/faction_rank.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Faction_t;

    class Faction_And_Rank_t
    {
    public:
        static Bool_t   Has_Same_Faction(const Faction_And_Rank_t& a, const Faction_And_Rank_t& b);

        static Int_t    Compare_Editor_Or_Form_IDs(Faction_And_Rank_t& a, Faction_And_Rank_t& b);

    public:
        maybe<Faction_t*>           faction;    // 00 (some instead?)
        some<Raw_Faction_Rank_t>    rank;       // 08
        u8                          pad_09;     // 09
        u16                         pad_0A;     // 0A
        u32                         pad_0C;     // 0C

    public:
        Faction_And_Rank_t(some<Faction_t*> faction, some<Raw_Faction_Rank_t> rank);

    public:
        Bool_t  Is_Valid();

        void    Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Faction_And_Rank_t) == 0x10);

    class Factions_And_Ranks_t :
        public Array_t<Faction_And_Rank_t>
    {
    public:
        using Array_t<Faction_And_Rank_t>::Array_t;

    public:
        maybe<Raw_Faction_Rank_t>   Faction_Rank(some<Faction_t*> faction);
        void                        Faction_Rank(some<Faction_t*> faction, some<Raw_Faction_Rank_t> rank);
    };

}
