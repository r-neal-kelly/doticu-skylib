/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Magic_Cast_Type_e :   // MagicSystem::CastingType
        public Enum_t<u8>       // 00
    {
    public:
        enum enum_type : value_type
        {
            CONSTANT        = 0,
            FIRE_AND_FORGET = 1,
            CONCENTRATION   = 2,
            SCROLL          = 3,
        };

    public:
        using Enum_t::Enum_t;
    };

}
