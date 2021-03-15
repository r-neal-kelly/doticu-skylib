/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Encounter_Zone_t;

    class Extra_Encounter_Zone_t :  // ExtraEncounterZone
        public Extra_Data_t         // 00
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
                V_TABLE = 0x0152C220, // 229555
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Extra_Encounter_Zone_t(); // 0

    public:
        Encounter_Zone_t* encounter_zone; // 10
    };
    STATIC_ASSERT(sizeof(Extra_Encounter_Zone_t) == 0x18);

}
