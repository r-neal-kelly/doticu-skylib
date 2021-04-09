/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value_bool.h"

namespace doticu_skylib {

    Bool_t Package_Value_Bool_t::Bool() const
    {
        SKYLIB_ASSERT(Is_Bool());

        return this->value != IS_FALSE;
    }

    void Package_Value_Bool_t::Bool(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Bool());

        if (value) {
            this->value = IS_TRUE;
        } else {
            this->value = IS_FALSE;
        }
    }

    Package_Value_Bool_t::operator Bool_t() const
    {
        return Bool();
    }

    Bool_t Package_Value_Bool_t::operator !() const
    {
        return !static_cast<Bool_t>(*this);
    }

    Package_Value_Bool_t& Package_Value_Bool_t::operator =(Bool_t value)
    {
        Bool(value);
        return *this;
    }

    void Package_Value_Bool_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Package_Value_Bool_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "value: %s", Bool() ? "true" : "false");

        SKYLIB_LOG(indent + "}");
    }

}
