/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Update_3D_Flags_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            MODEL               = static_cast<value_type>(1 << 0),
            SKIN                = static_cast<value_type>(1 << 1),
            HEAD                = static_cast<value_type>(1 << 2),
            FACE                = static_cast<value_type>(1 << 3),
            SCALE               = static_cast<value_type>(1 << 4),
            SKELETON            = static_cast<value_type>(1 << 5),
            INITIALIZE_DEFAULT  = static_cast<value_type>(1 << 6),
            SKY_CELL_SKIN       = static_cast<value_type>(1 << 7),
        };
        using Enum_t::Enum_t;
    };

}
