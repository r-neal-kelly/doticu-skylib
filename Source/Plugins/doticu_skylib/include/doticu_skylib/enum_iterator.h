/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Iterator_e :
        public Enum_t<Word_t>
    {
    public:
        enum enum_type : value_type
        {
            CONTINUE    = 0,
            BREAK       = 1,
        };

    public:
        using Enum_t::Enum_t;
    };

}
