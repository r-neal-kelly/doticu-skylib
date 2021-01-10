/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Interaction_t;

    class Interaction_x : public Data_x // ExtraInteraction
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
        virtual ~Interaction_x();

    public:
        Interaction_t* interaction; // 10 (smart ptr?)
    };
    STATIC_ASSERT(sizeof(Interaction_x) == 0x18);

}
