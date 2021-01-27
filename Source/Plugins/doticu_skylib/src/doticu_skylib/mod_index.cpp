/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/mod_index.h"

namespace doticu_skylib {

    Heavy_Mod_Index_t::Heavy_Mod_Index_t(value_type value) :
        value(value)
    {
    }

    Heavy_Mod_Index_t::operator value_type() const
    {
        return this->value;
    }

    Heavy_Mod_Index_t::operator Bool_t() const
    {
        return (this->value < NONE_VALUE) && (this->value != 0xFE);
    }

    Bool_t Heavy_Mod_Index_t::operator !() const
    {
        return !static_cast<Bool_t>(*this);
    }

    template <>
    Bool_t Is_Equal(const none<Heavy_Mod_Index_t>& a, const Heavy_Mod_Index_t& b)
    {
        return !b;
    }

    Light_Mod_Index_t::Light_Mod_Index_t(value_type value) :
        value(value)
    {
    }

    Light_Mod_Index_t::operator value_type() const
    {
        return this->value;
    }

    Light_Mod_Index_t::operator Bool_t() const
    {
        return this->value < NONE_VALUE;
    }

    Bool_t Light_Mod_Index_t::operator !() const
    {
        return !static_cast<Bool_t>(*this);
    }

    template <>
    Bool_t Is_Equal(const none<Light_Mod_Index_t>& a, const Light_Mod_Index_t& b)
    {
        return !b;
    }

}
