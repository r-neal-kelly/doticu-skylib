/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Dialogue_Topic_Subtype_e : public Enum_t<u16>
    {
    public:
        enum : value_type
        {
            CUSTOM      = 0,
            FORCE_GREET = 1,
            RUMORS      = 2,
            // ...
        };
        using Enum_t::Enum_t;
    };

}
