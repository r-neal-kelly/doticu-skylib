/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Interaction_t;

    class Extra_Interaction_t : // ExtraInteraction
        public Extra_Data_t     // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::INTERACTION,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152F540,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Extra_Interaction_t(); // 0

    public:
        Interaction_t* interaction; // 10 (smart ptr?)
    };
    STATIC_ASSERT(sizeof(Extra_Interaction_t) == 0x18);

}
