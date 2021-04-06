/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value_int.h"

namespace doticu_skylib {

    Int_t Package_Value_Int_t::Value() const
    {
        SKYLIB_ASSERT(Type() == Package_Value_Type_e::INT);

        return this->value;
    }

    void Package_Value_Int_t::Value(Int_t value)
    {
        SKYLIB_ASSERT(Type() == Package_Value_Type_e::INT);

        this->value = value;
    }

    Package_Value_Int_t::operator Int_t() const
    {
        return Value();
    }

    Package_Value_Int_t& Package_Value_Int_t::operator =(Int_t value)
    {
        Value(value);
        return *this;
    }

    void Package_Value_Int_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Package_Value_Int_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "value: %i", Value());

        SKYLIB_LOG(indent + "}");
    }

}
