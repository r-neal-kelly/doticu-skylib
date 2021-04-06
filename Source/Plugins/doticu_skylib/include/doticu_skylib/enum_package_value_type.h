/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Package_Value_Type_e :
        public Enum_t<s64>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = -1,

            BOOL,
            FLOAT,
            INT,
            LIST,
            LOCATION,
            REFERENCE,
            TARGET,
            TOPIC,

            _TOTAL_,
        };

    public:
        using Enum_t::Enum_t;
    };

}
