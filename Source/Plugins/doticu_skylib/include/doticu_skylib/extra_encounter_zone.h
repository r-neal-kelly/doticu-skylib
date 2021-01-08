/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Encounter_Zone_t;

    class Encounter_Zone_x : public Data_x // ExtraEncounterZone
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::ENCOUNTER_ZONE,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152C220,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Encounter_Zone_x();

    public:
        Encounter_Zone_t* encounter_zone; // 10
    };
    STATIC_ASSERT(sizeof(Encounter_Zone_x) == 0x18);

}
