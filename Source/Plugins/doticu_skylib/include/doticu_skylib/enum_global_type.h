/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Global_Type_e : Enum_t<char>
    {
    public:
        enum : value_type
        {
            FLOAT   = 'f',
            SHORT   = 's',
            LONG    = 'l',
        };
        using Enum_t::Enum_t;
    };

}
