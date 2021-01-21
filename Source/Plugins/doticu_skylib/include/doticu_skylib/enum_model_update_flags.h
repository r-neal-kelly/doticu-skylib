/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Model_Update_Flags_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            MODEL       = static_cast<value_type>(1 << 0),
            SKIN        = static_cast<value_type>(1 << 1),
            HEAD        = static_cast<value_type>(1 << 2),
            FACE        = static_cast<value_type>(1 << 3),
            SCALE       = static_cast<value_type>(1 << 4),
            SKELETON    = static_cast<value_type>(1 << 5),
            UNKNOWN_6   = static_cast<value_type>(1 << 6), // initialize to default settings?
            UNKNOWN_7   = static_cast<value_type>(1 << 7), // something to do with the sky?
        };
        using Enum_t::Enum_t;
    };

}
