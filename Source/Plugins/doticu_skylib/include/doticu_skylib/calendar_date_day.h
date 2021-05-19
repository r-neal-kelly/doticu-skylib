/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/numeric.h"

namespace doticu_skylib {

    class Calendar_Date_Day_t_data :
        public Numeric_Data_t<s8>
    {
    public:
        static constexpr value_type _NONE_  = 0;
        static constexpr value_type _MIN_   = 1;
        static constexpr value_type _MAX_   = 31;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return value >= _MIN_ && value <= _MAX_;
        }
    };

    class Calendar_Date_Day_t :
        public Numeric_t<Calendar_Date_Day_t_data>
    {
    public:
        using Numeric_t::Numeric_t;
    };

    template <>
    class none<Calendar_Date_Day_t> :
        public none_numeric<Calendar_Date_Day_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<Calendar_Date_Day_t> :
        public maybe_numeric<Calendar_Date_Day_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Calendar_Date_Day_t> :
        public some_numeric<Calendar_Date_Day_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
