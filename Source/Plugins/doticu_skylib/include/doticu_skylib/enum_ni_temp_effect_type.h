/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class NI_Temp_Effect_Type_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            _NONE_              = static_cast<value_type>(~0),

            TERRAIN             = static_cast<value_type>(0),
            WEAPON_BLOOD        = static_cast<value_type>(1),
            DECAL               = static_cast<value_type>(2),
            GEOMETRY_DECAL      = static_cast<value_type>(3),
            PARTICLE            = static_cast<value_type>(4),
            DEBRIS              = static_cast<value_type>(5),
            SPG                 = static_cast<value_type>(6),
            DEFAULT             = static_cast<value_type>(7),
            REFERENCE_DEFAULT   = static_cast<value_type>(8),
            REFERENCE_MODEL     = static_cast<value_type>(9),
            REFERENCE_SHADER    = static_cast<value_type>(10),
            MAGIC_SUMMON        = static_cast<value_type>(11),
        };
        using Enum_t::Enum_t;
    };

}
