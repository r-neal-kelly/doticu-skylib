/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Dialogue_Topic_Type_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            SCENE       = 2,
            COMBAT      = 3,
            FAVORS      = 4,
            DETECTION   = 5,
            SERVICE     = 6,
            MISC        = 7,

            _TOTAL_     = 6,
        };
        using Enum_t::Enum_t;
    };

}
