/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/numeric.h"

namespace doticu_skylib {

    class Calendar_Time_Hour_24_t_data :
        public Numeric_Data_t<s8>
    {
    public:
        static constexpr value_type _NONE_  = -1;
        static constexpr value_type _MIN_   = 0;
        static constexpr value_type _MAX_   = 23;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return value >= _MIN_ && value <= _MAX_;
        }
    };

    class Calendar_Time_Hour_24_t :
        public Numeric_t<Calendar_Time_Hour_24_t_data>
    {
    public:
        using Numeric_t::Numeric_t;
    };

    template <>
    class none<Calendar_Time_Hour_24_t> :
        public none_numeric<Calendar_Time_Hour_24_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<Calendar_Time_Hour_24_t> :
        public maybe_numeric<Calendar_Time_Hour_24_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Calendar_Time_Hour_24_t> :
        public some_numeric<Calendar_Time_Hour_24_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
