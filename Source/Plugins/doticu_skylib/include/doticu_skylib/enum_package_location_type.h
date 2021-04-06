/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Package_Location_Type_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            NEAR_REFERENCE  = 0,    // handle
            NEAR_SELF       = 12,   // nullptr
        };

    public:
        using Enum_t::Enum_t;
    };

}
