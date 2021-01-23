/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Magic_Delivery_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            SELF            = 0,
            TOUCH           = 1,
            AIMED           = 2,
            TARGET_ACTOR    = 3,
            TARGET_LOCATION = 4,
        };
        using Enum_t::Enum_t;
    };

}
