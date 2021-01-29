/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class NI_3D_Flags_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            HIDDEN          = static_cast<value_type>(1 << 0),
            // ...
            FORCE_UPDATE    = static_cast<value_type>(1 << 25),
        };
        using Enum_t::Enum_t;
    };

}
