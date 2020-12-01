/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Faction_t;

    using Faction_Rank_t = s8;

    class Faction_And_Rank_t
    {
    public:
        Faction_t*      faction;    // 00
        Faction_Rank_t  rank;       // 08
        u8              pad_09;     // 09
        u16             pad_0A;     // 0A
        u32             pad_0C;     // 0C
    };
    STATIC_ASSERT(sizeof(Faction_And_Rank_t) == 0x10);

}
