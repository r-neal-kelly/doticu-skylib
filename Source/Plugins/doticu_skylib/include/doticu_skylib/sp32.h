/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/math.h"
#include "doticu_skylib/numeric.h"

namespace doticu_skylib {

    class sp32_data :
        public Numeric_Data_t<s32>
    {
    public:
        static constexpr value_type _NONE_  = 0;
        static constexpr value_type _MIN_   = _NONE_;
        static constexpr value_type _MAX_   = std::numeric_limits<value_type>::max();

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return value >= _MIN_;
        }
    };

    class sp32 :
        public Numeric_t<sp32_data>
    {
    public:
        using Numeric_t::Numeric_t;
    };

    template <>
    class none<sp32> :
        public none_numeric<sp32>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<sp32> :
        public maybe_numeric<sp32>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<sp32> :
        public some_numeric<sp32>
    {
    public:
        using some_numeric::some_numeric;
    };

}
