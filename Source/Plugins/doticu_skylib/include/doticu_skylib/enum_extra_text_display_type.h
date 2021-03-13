/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Extra_Text_Display_Type_e :
        public Enum_t<s32>
    {
    public:
        enum enum_type : value_type
        {
            DEFAULT = -1,
            CUSTOM  = -2,
        };

    public:
        using Enum_t::Enum_t;
    };

}
