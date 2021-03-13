/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Magic_Delivery_Type_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_              = static_cast<value_type>(-1),

            SELF                = static_cast<value_type>(0),
            TOUCH               = static_cast<value_type>(1),
            AIMED_PROJECTILE    = static_cast<value_type>(2),
            CROSSHAIR_ACTOR     = static_cast<value_type>(3),
            CROSSHAIR_LOCATION  = static_cast<value_type>(4),

            _TOTAL_             = static_cast<value_type>(5),
        };

    public:
        using Enum_t::Enum_t;
    };

}
