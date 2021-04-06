/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value_location.h"

namespace doticu_skylib {

    maybe<Package_Location_t*> Package_Value_Location_t::Value() const
    {
        SKYLIB_ASSERT(Type() == Package_Value_Type_e::LOCATION);

        return this->value;
    }

    void Package_Value_Location_t::Value(maybe<Package_Location_t*> value)
    {
        SKYLIB_ASSERT(Type() == Package_Value_Type_e::LOCATION);

        this->value = value;
    }

    Package_Value_Location_t::operator maybe<Package_Location_t*>() const
    {
        return Value();
    }

    Package_Value_Location_t& Package_Value_Location_t::operator =(maybe<Package_Location_t*> value)
    {
        Value(value);
        return *this;
    }

    void Package_Value_Location_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Package_Value_Location_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "value: 0x%p", Value());

        SKYLIB_LOG(indent + "}");
    }

}
