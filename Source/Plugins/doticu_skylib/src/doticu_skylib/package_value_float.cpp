/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value_float.h"

namespace doticu_skylib {

    Float_t Package_Value_Float_t::Value() const
    {
        SKYLIB_ASSERT(Type() == Package_Value_Type_e::FLOAT);

        return this->value;
    }

    void Package_Value_Float_t::Value(Float_t value)
    {
        SKYLIB_ASSERT(Type() == Package_Value_Type_e::FLOAT);

        this->value = value;
    }

    Package_Value_Float_t::operator Float_t() const
    {
        return Value();
    }

    Package_Value_Float_t& Package_Value_Float_t::operator =(Float_t value)
    {
        Value(value);
        return *this;
    }

    void Package_Value_Float_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Package_Value_Float_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "value: %f", Value());

        SKYLIB_LOG(indent + "}");
    }

}
