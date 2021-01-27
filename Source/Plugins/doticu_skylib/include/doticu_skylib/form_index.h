/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe_numeric.h"

namespace doticu_skylib {

    using Raw_Form_Index_t = u32;

    /* Heavy_Form_Index_t */

    class Heavy_Form_Index_t
    {
    public:
        using value_type = Raw_Form_Index_t;

    public:
        static constexpr value_type NONE_VALUE = 0x01000000;

    protected:
        value_type value;

    public:
        Heavy_Form_Index_t(value_type value);

    public:
        operator            value_type() const;
        explicit operator   Bool_t() const;
        Bool_t operator     !() const;
    };

    template <>
    Bool_t Is_Equal(const none<Heavy_Form_Index_t>& a, const Heavy_Form_Index_t& b);

    template <>
    class none<Heavy_Form_Index_t> : public none_numeric<Heavy_Form_Index_t>
    {
    public:
        none() : none_numeric(Heavy_Form_Index_t::NONE_VALUE) {}
    };

    template <>
    class maybe<Heavy_Form_Index_t> : public maybe_numeric<Heavy_Form_Index_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Heavy_Form_Index_t> : public some_numeric<Heavy_Form_Index_t>
    {
    public:
        using some_numeric::some_numeric;
    };

    /* Light_Form_Index_t */

    class Light_Form_Index_t
    {
    public:
        using value_type = Raw_Form_Index_t;

    public:
        static constexpr value_type NONE_VALUE = 0x1000;

    protected:
        value_type value;

    public:
        Light_Form_Index_t(value_type value);

    public:
        operator            value_type() const;
        explicit operator   Bool_t() const;
        Bool_t operator     !() const;
    };

    template <>
    Bool_t Is_Equal(const none<Light_Form_Index_t>& a, const Light_Form_Index_t& b);

    template <>
    class none<Light_Form_Index_t> : public none_numeric<Light_Form_Index_t>
    {
    public:
        none() : none_numeric(Light_Form_Index_t::NONE_VALUE) {}
    };

    template <>
    class maybe<Light_Form_Index_t> : public maybe_numeric<Light_Form_Index_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Light_Form_Index_t> : public some_numeric<Light_Form_Index_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
