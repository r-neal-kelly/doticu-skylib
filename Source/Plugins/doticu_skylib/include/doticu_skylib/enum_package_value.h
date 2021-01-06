/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Package_Value_e : public Enum_t<Word_t>
    {
    public:
        enum : value_type
        {
            NONE = 0,

            BOOL,
            INT,
            FLOAT,
            LOCATION,
            REFERENCE, // SINGLE_REFERENCE
            TOPIC,

            _END_,
        };
        using Enum_t::Enum_t;
    };

}
