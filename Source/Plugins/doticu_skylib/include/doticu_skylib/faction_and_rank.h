/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/faction_rank.h"

namespace doticu_skylib {

    class Faction_t;

    class Faction_And_Rank_t
    {
    public:
        static Bool_t   Has_Same_Faction(const Faction_And_Rank_t& a, const Faction_And_Rank_t& b);

        static Int_t    Compare_Editor_Or_Form_IDs(Faction_And_Rank_t* a, Faction_And_Rank_t* b);

    public:
        Faction_t*      faction;    // 00
        Faction_Rank_t  rank;       // 08
        u8              pad_09;     // 09
        u16             pad_0A;     // 0A
        u32             pad_0C;     // 0C

    public:
        Bool_t  Is_Valid();

        void    Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Faction_And_Rank_t) == 0x10);

}
