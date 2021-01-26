/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe_numeric.h"

namespace doticu_skylib {

    class Mod_Index_t
    {
    private:
        u16 value;

    public:
        Mod_Index_t(u16 value) : value(value) {}

        operator u16() const { return value; }
    };

    class Heavy_Mod_Index_t : public Mod_Index_t
    {
    public:
        using Mod_Index_t::Mod_Index_t;
        // once we have a wrapper for Form_ID_t, we can take that as well
    };

    template <>
    class none<Heavy_Mod_Index_t> : public none_numeric<Heavy_Mod_Index_t>
    {
    public:
        none() : none_numeric(0x100) {}
    };

    template <>
    inline Bool_t Is_Equal(const none<Heavy_Mod_Index_t>& a, const Heavy_Mod_Index_t& b)
    {
        return b == 0xFE || b >= a.value;
    }

    template <>
    class maybe<Heavy_Mod_Index_t> : public maybe_numeric<Heavy_Mod_Index_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Heavy_Mod_Index_t> : public some_numeric<Heavy_Mod_Index_t>
    {
    public:
        using some_numeric::some_numeric;
    };

    class Light_Mod_Index_t : public Mod_Index_t
    {
    public:
        using Mod_Index_t::Mod_Index_t;
    };

    template <>
    class none<Light_Mod_Index_t> : public none_numeric<Light_Mod_Index_t>
    {
    public:
        none() : none_numeric(0x1000) {}
    };

    template <>
    inline Bool_t Is_Equal(const none<Light_Mod_Index_t>& a, const Light_Mod_Index_t& b)
    {
        return b >= a.value;
    }

    template <>
    class maybe<Light_Mod_Index_t> : public maybe_numeric<Light_Mod_Index_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Light_Mod_Index_t> : public some_numeric<Light_Mod_Index_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
