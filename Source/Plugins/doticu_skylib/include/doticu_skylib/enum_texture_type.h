/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Texture_Type_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            DIFFUSE             = 0x0,
            NORMAL              = 0x1,
            GLOSS               = 0x1,
            ENVIRONMENT_MASK    = 0x2,
            SUBSURFACE_TINT     = 0x2,
            GLOW_MAP            = 0x3,
            DETAIL_MAP          = 0x3,
            HEIGHT              = 0x4,
            ENVIRONMENT         = 0x5,
            MULTILAYER          = 0x6,
            BACKLIGHT_MASK      = 0x7,
            SPECULAR            = 0x7,

            _TOTAL_             = 0x8,
        };
        using Enum_t::Enum_t;
    };

}
