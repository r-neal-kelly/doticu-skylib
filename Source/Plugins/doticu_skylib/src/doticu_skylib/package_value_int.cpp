/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value_int.h"

namespace doticu_skylib {

    Int_t Package_Value_Int_t::Int() const
    {
        SKYLIB_ASSERT(Is_Int());

        return this->value;
    }

    void Package_Value_Int_t::Int(Int_t value)
    {
        SKYLIB_ASSERT(Is_Int());

        this->value = value;
    }

    Package_Value_Int_t::operator Int_t() const
    {
        return Int();
    }

    Package_Value_Int_t& Package_Value_Int_t::operator =(Int_t value)
    {
        Int(value);
        return *this;
    }

    void Package_Value_Int_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Package_Value_Int_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "value: %i", Int());

        SKYLIB_LOG(indent + "}");
    }

}
