/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Location_t;

    class Extra_Location_t :    // ExtraLocation
        public Extra_Data_t     // 00
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
                V_TABLE = 0x0152C180, // 229550
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Extra_Location_t(); // 0

    public:
        maybe<Location_t*>  location; // 10
    };
    STATIC_ASSERT(sizeof(Extra_Location_t) == 0x18);

}
