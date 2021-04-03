/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/math.h"
#include "doticu_skylib/numeric.h"

namespace doticu_skylib {

    using Raw_Container_Entry_Count_t = s32;

    class Container_Entry_Count_t_data :
        public Numeric_Data_t<Raw_Container_Entry_Count_t>
    {
    public:
        static constexpr value_type _NONE_  = 0;
        static constexpr value_type _MIN_   = _NONE_;
        static constexpr value_type _MAX_   = std::numeric_limits<value_type>::max();

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return value >= _NONE_;
        }
    };

    class Container_Entry_Count_t :
        public Numeric_t<Container_Entry_Count_t_data>
    {
    public:
        using Numeric_t::Numeric_t;
    };

    template <>
    class none<Container_Entry_Count_t> :
        public none_numeric<Container_Entry_Count_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<Container_Entry_Count_t> :
        public maybe_numeric<Container_Entry_Count_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Container_Entry_Count_t> :
        public some_numeric<Container_Entry_Count_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
