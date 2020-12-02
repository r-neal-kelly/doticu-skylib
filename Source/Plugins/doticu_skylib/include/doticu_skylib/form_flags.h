/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Form_Flags_e : public Enum_t<u32>
    {
    public:
        enum : u32
        {
            IS_MASTER   = 1 << 0,

            IS_ALTERED  = 1 << 1,
            IS_PLAYABLE = 1 << 2,

            IS_DELETED  = 1 << 5,
        };
        using Enum_t::Enum_t;
    };

}
