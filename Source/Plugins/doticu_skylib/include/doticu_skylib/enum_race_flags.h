/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Race_Flags_1_e :
        public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            IS_PLAYABLE         = static_cast<value_type>(1 << 0),
            IS_CHILD            = static_cast<value_type>(1 << 2),
            CAN_TALK_TO_PLAYER  = static_cast<value_type>(1 << 21),
        };
        using Enum_t::Enum_t;
    };

    class Race_Flags_2_e :
        public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            ISNT_HOSTILE = static_cast<value_type>(1 << 1),
        };
        using Enum_t::Enum_t;
    };

}
