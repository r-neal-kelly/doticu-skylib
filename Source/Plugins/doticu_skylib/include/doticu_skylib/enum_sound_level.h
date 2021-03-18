/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Sound_Level_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            LOUD        = 0,
            NORMAL      = 1,
            SILENT      = 2,
            VERY_LOUD   = 3,
            QUIET       = 4,
        };

    public:
        using Enum_t::Enum_t;
    };

}
