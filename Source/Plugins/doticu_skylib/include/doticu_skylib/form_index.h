/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/numeric.h"

namespace doticu_skylib {

    using Raw_Form_Index_t = u32;

    /* Heavy_Form_Index_t */

    class Heavy_Form_Index_t_data :
        public Numeric_Data_t<Raw_Form_Index_t>
    {
    public:
        static constexpr value_type _NONE_  = 0x01000000;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return value < _NONE_;
        }
    };

    class Heavy_Form_Index_t :
        public Numeric_t<Heavy_Form_Index_t_data>
    {
    public:
        using Numeric_t::Numeric_t;
    };

    template <>
    class none<Heavy_Form_Index_t> :
        public none_numeric<Heavy_Form_Index_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<Heavy_Form_Index_t> :
        public maybe_numeric<Heavy_Form_Index_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Heavy_Form_Index_t> :
        public some_numeric<Heavy_Form_Index_t>
    {
    public:
        using some_numeric::some_numeric;
    };

    /* Light_Form_Index_t */

    class Light_Form_Index_t_data :
        public Numeric_Data_t<Raw_Form_Index_t>
    {
    public:
        static constexpr value_type _NONE_  = 0x1000;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return value < _NONE_;
        }
    };

    class Light_Form_Index_t :
        public Numeric_t<Light_Form_Index_t_data>
    {
    public:
        using Numeric_t::Numeric_t;
    };

    template <>
    class none<Light_Form_Index_t> :
        public none_numeric<Light_Form_Index_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<Light_Form_Index_t> :
        public maybe_numeric<Light_Form_Index_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Light_Form_Index_t> :
        public some_numeric<Light_Form_Index_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
