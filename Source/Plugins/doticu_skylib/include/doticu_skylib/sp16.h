/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/math.h"
#include "doticu_skylib/numeric.h"

namespace doticu_skylib {

    class sp16_data :
        public Numeric_Data_t<s16>
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

    class sp16 :
        public Numeric_t<sp16_data>
    {
    public:
        using Numeric_t::Numeric_t;
    };

    template <>
    class none<sp16> :
        public none_numeric<sp16>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<sp16> :
        public maybe_numeric<sp16>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<sp16> :
        public some_numeric<sp16>
    {
    public:
        using some_numeric::some_numeric;
    };

}
