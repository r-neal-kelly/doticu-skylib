/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Actor_AI_Type_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            _NONE_      = static_cast<value_type>(~0),

            HIGH        = static_cast<value_type>(0),
            MIDDLE_HIGH = static_cast<value_type>(1),
            MIDDLE_LOW  = static_cast<value_type>(2),
            LOW         = static_cast<value_type>(3),
        };
        using Enum_t::Enum_t;
    };

}
