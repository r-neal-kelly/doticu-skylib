/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/numeric.h"

namespace doticu_skylib {

    using Raw_Alpha_t = Float_t;

    class Alpha_t_data :
        public Numeric_Data_t<Raw_Alpha_t>
    {
    public:
        static constexpr value_type _NONE_  = 0.0f;
        static constexpr value_type _MAX_   = 1.0f;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return value > _NONE_ && value <= _MAX_;
        }
    };

    class Alpha_t :
        public Numeric_t<Alpha_t_data>
    {
    public:
        using Numeric_t::Numeric_t;
    };

    template <>
    class none<Alpha_t> :
        public none_numeric<Alpha_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<Alpha_t> :
        public maybe_numeric<Alpha_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Alpha_t> :
        public some_numeric<Alpha_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
