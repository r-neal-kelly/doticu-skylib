/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/numeric.h"

namespace doticu_skylib {

    using Raw_Mod_Index_t = u16;

    /* Heavy_Mod_Index_t */

    class Heavy_Mod_Index_t_data :
        public Numeric_Data_t<Raw_Mod_Index_t>
    {
    public:
        static constexpr value_type _NONE_  = 0x100;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return (value < _NONE_) && (value != 0xFE);
        }
    };

    class Heavy_Mod_Index_t :
        public Numeric_t<Heavy_Mod_Index_t_data>
    {
    public:
        using Numeric_t::Numeric_t;
    };

    template <>
    class none<Heavy_Mod_Index_t> :
        public none_numeric<Heavy_Mod_Index_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<Heavy_Mod_Index_t> :
        public maybe_numeric<Heavy_Mod_Index_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Heavy_Mod_Index_t> :
        public some_numeric<Heavy_Mod_Index_t>
    {
    public:
        using some_numeric::some_numeric;
    };

    /* Light_Mod_Index_t */

    class Light_Mod_Index_t_data :
        public Numeric_Data_t<Raw_Mod_Index_t>
    {
    public:
        static constexpr value_type _NONE_  = 0x1000;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return value < _NONE_;
        }
    };

    class Light_Mod_Index_t :
        public Numeric_t<Light_Mod_Index_t_data>
    {
    public:
        using Numeric_t::Numeric_t;
    };

    template <>
    class none<Light_Mod_Index_t> :
        public none_numeric<Light_Mod_Index_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<Light_Mod_Index_t> :
        public maybe_numeric<Light_Mod_Index_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Light_Mod_Index_t> :
        public some_numeric<Light_Mod_Index_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
