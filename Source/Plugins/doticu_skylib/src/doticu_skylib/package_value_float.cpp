/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value_float.h"

namespace doticu_skylib {

    Float_t Package_Value_Float_t::Float() const
    {
        SKYLIB_ASSERT(Is_Float());

        return this->value;
    }

    void Package_Value_Float_t::Float(Float_t value)
    {
        SKYLIB_ASSERT(Is_Float());

        this->value = value;
    }

    Package_Value_Float_t::operator Float_t() const
    {
        return Float();
    }

    Package_Value_Float_t& Package_Value_Float_t::operator =(Float_t value)
    {
        Float(value);
        return *this;
    }

    void Package_Value_Float_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Package_Value_Float_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "value: %f", Float());

        SKYLIB_LOG(indent + "}");
    }

}
