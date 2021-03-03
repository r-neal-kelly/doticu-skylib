/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Texture_Set_Flags_e :
        public Enum_t<u16>
    {
    public:
        enum enum_type : value_type
        {
            HAS_NO_SPECULAR_MAP         = static_cast<value_type>(1 << 0),
            ARE_FACE_GEN_TEXTURES       = static_cast<value_type>(1 << 1),
            HAS_MODEL_SPACE_NORMAL_MAP  = static_cast<value_type>(1 << 2),
        };
        using Enum_t::Enum_t;
    };

}
