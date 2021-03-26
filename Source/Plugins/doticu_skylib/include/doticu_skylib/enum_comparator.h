/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Comparator_e :
        public Enum_t<Int_t>
    {
    public:
        enum enum_type : value_type
        {
            IS_ORDERED      = static_cast<value_type>(-1),
            IS_UNORDERED    = static_cast<value_type>(1),
            IS_EQUAL        = static_cast<value_type>(0),
        };

    public:
        using Enum_t::Enum_t;
    };

}
