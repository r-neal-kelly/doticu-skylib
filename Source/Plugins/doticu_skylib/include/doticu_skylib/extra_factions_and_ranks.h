/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"

#include "doticu_skylib/faction_and_rank.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Faction_t;

    class Factions_And_Ranks_x : public Data_x
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::FACTIONS_AND_RANKS,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                V_TABLE = 0x0152C800,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Factions_And_Ranks_x();

        Array_t<Faction_And_Rank_t> factions_and_ranks;         // 10
        Faction_t*                  crime_faction;              // 28
        Bool_t                      do_remove_crime_faction;    // 30
        u8                          pad_31;                     // 31
        u16                         pad_32;                     // 32
        u32                         pad_34;                     // 34
    };
    STATIC_ASSERT(sizeof(Factions_And_Ranks_x) == 0x38);

}
