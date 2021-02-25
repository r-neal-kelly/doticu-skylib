/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/extra_data.h"
#include "doticu_skylib/faction_and_rank.h"

namespace doticu_skylib {

    class Faction_t;

    class Extra_Factions_t :    // ExtraFactionChanges
        public Extra_Data_t     // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::FACTIONS,
        };

        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                V_TABLE = 0x0152C800, // 229602
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Factions_t*>  Create(maybe<Faction_t*> crime_faction);
        static void                     Destroy(some<Extra_Factions_t*> x_factions);

    public:
        virtual ~Extra_Factions_t(); // 0

    public:
        Array_t<Faction_And_Rank_t> factions_and_ranks; // 10
        maybe<Faction_t*>           crime_faction;      // 28
        Bool_t                      unk_30;             // 30
        u8                          pad_31;             // 31
        u16                         pad_32;             // 32
        u32                         pad_34;             // 34
    };
    STATIC_ASSERT(sizeof(Extra_Factions_t) == 0x38);

}
