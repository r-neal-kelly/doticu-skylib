/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/math.h"
#include "doticu_skylib/numeric.h"

namespace doticu_skylib {

    class sn32_data :
        public Numeric_Data_t<s32>
    {
    public:
        static constexpr value_type _NONE_  = 0;
        static constexpr value_type _MIN_   = std::numeric_limits<value_type>::min();
        static constexpr value_type _MAX_   = _NONE_;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return value <= _MAX_;
        }
    };

    class sn32 :
        public Numeric_t<sn32_data>
    {
    public:
        using Numeric_t::Numeric_t;
    };

    template <>
    class none<sn32> :
        public none_numeric<sn32>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<sn32> :
        public maybe_numeric<sn32>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<sn32> :
        public some_numeric<sn32>
    {
    public:
        using some_numeric::some_numeric;
    };

}
