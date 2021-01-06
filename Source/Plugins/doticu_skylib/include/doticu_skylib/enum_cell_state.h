/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Cell_State_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            IS_ATTACHED = 7,
        };
        using Enum_t::Enum_t;
    };

}
