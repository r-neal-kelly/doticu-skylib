/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Location_t;

    class Location_x : public Data_x
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::LOCATION,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                V_TABLE = 0x0152C180,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Location_x();

        Location_t* location; // 10
    };
    STATIC_ASSERT(sizeof(Location_x) == 0x18);

}
