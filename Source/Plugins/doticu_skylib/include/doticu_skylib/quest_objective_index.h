/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/math.h"
#include "doticu_skylib/numeric.h"

namespace doticu_skylib {

    class Quest_Objective_Index_t_data :
        public Numeric_Data_t<u16>
    {
    public:
        static constexpr value_type _NONE_  = 0;
        static constexpr value_type _MIN_   = 0;
        static constexpr value_type _MAX_   = std::numeric_limits<value_type>::max();

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return true;
        }
    };

    class Quest_Objective_Index_t :
        public Numeric_t<Quest_Objective_Index_t_data>
    {
    public:
        using Numeric_t::Numeric_t;
    };

}
