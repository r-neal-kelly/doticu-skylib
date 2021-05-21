/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Relation_Flags_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_      = 0,

            IS_SECRET   = static_cast<value_type>(1 << 7),
        };

    public:
        using Enum_t::Enum_t;
    };

}
