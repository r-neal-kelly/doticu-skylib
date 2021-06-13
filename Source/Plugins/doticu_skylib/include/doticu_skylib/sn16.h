/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/math.h"
#include "doticu_skylib/numeric.h"

namespace doticu_skylib {

    class sn16_data :
        public Numeric_Data_t<s16>
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

    class sn16 :
        public Numeric_t<sn16_data>
    {
    public:
        using Numeric_t::Numeric_t;
    };

    template <>
    class none<sn16> :
        public none_numeric<sn16>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<sn16> :
        public maybe_numeric<sn16>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<sn16> :
        public some_numeric<sn16>
    {
    public:
        using some_numeric::some_numeric;
    };

}
