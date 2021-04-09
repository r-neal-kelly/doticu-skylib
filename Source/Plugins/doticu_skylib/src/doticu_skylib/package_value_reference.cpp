/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_target.h"
#include "doticu_skylib/package_value_reference.h"

namespace doticu_skylib {

    maybe<Package_Target_t*> Package_Value_Reference_t::Target() const
    {
        SKYLIB_ASSERT(Is_Reference());

        return this->value;
    }

    void Package_Value_Reference_t::Target(maybe<Package_Target_t*> value)
    {
        SKYLIB_ASSERT(Is_Reference());

        this->value = value;
    }

    Package_Value_Reference_t::operator maybe<Package_Target_t*>() const
    {
        return Target();
    }

    Package_Value_Reference_t& Package_Value_Reference_t::operator =(maybe<Package_Target_t*> value)
    {
        Target(value);
        return *this;
    }

    void Package_Value_Reference_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Package_Value_Reference_t::Log");
        SKYLIB_LOG(indent + "{");

        maybe<Package_Target_t*> target = Target();
        if (target) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "target:");
            target->Log(indent + SKYLIB_TAB + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "target: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}
