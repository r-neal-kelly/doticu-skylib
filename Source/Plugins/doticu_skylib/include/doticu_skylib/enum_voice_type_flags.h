/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Voice_Type_Flags_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            ALLOW_DEFAULT_DIALOGUE  = static_cast<value_type>(1 << 0),
            IS_FEMALE               = static_cast<value_type>(1 << 1),
        };
        using Enum_t::Enum_t;
    };

}
