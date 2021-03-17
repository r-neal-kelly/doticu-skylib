/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Book_Type_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_          = static_cast<value_type>(-128),

            NOTE_OR_SCROLL  = static_cast<value_type>(-1),
            CODEX           = static_cast<value_type>(0),

            _TOTAL_         = static_cast<value_type>(2),
        };

    public:
        using Enum_t::Enum_t;
    };

}
