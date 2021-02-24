/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Form_Flags_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            IS_MASTER   = 1 << 0,

            IS_ALTERED  = 1 << 1,
            IS_PLAYABLE = 1 << 2,

            IS_DELETED  = 1 << 5,
        };
        using Enum_t::Enum_t;
    };

    class Form_Flags_Extra_e :
        public Enum_t<u16>
    {
    public:
        enum enum_type : value_type
        {
        };
        using Enum_t::Enum_t;
    };

}
