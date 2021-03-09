/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_encounter_zone_flags.h"

#include "doticu_skylib/faction_rank.h"
#include "doticu_skylib/form.h"

namespace doticu_skylib {

    class Faction_t;
    class Location_t;

    class Encounter_Zone_t :    // BGSEncounterZone
        public Form_t           // 00
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ENCOUNTER_ZONE,
        };

    public:
        class Form_Change_Flags_e :
            public Enum_t<u32>
        {
        public:
            enum enum_type : value_type
            {
                FLAGS           = static_cast<value_type>(1 << 1),
                TIMES_OR_LEVEL  = static_cast<value_type>(1 << 31), // this may include more
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Encounter_Zone_t(); // 0

    public:
        maybe<Faction_t*>       owner;                  // 20
        maybe<Location_t*>      location;               // 28
        Raw_Faction_Rank_t      required_owner_rank;    // 30
        s8                      min_level;              // 31
        Encounter_Zone_Flags_e  encounter_zone_flags;   // 32
        s8                      max_level;              // 33
        u32                     pad_34;                 // 34
        u32                     detach_time;            // 38
        u32                     attach_time;            // 3C
        u32                     reset_time;             // 40
        u16                     zone_level;             // 44
        u16                     pad_46;                 // 46
    };
    STATIC_ASSERT(sizeof(Encounter_Zone_t) == 0x48);

}
