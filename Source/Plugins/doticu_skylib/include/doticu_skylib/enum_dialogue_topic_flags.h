/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Dialogue_Topic_Flags_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            DO_ALL_BEFORE_REPEATING = static_cast<value_type>(1 << 0),
        };
        using Enum_t::Enum_t;
    };

}
