/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Dialogue_Branch_Type_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            PLAYER  = 0,
            COMMAND = 1,

            _TOTAL_ = 2,
        };
        using Enum_t::Enum_t;
    };

}
