/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_location.h"
#include "doticu_skylib/package_value_location.h"

namespace doticu_skylib {

    maybe<Package_Location_t*> Package_Value_Location_t::Location() const
    {
        SKYLIB_ASSERT(Is_Location());

        return this->value;
    }

    void Package_Value_Location_t::Location(maybe<Package_Location_t*> value)
    {
        SKYLIB_ASSERT(Is_Location());

        this->value = value;
    }

    Package_Value_Location_t::operator maybe<Package_Location_t*>() const
    {
        return Location();
    }

    Package_Value_Location_t& Package_Value_Location_t::operator =(maybe<Package_Location_t*> value)
    {
        Location(value);
        return *this;
    }

    void Package_Value_Location_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Package_Value_Location_t::Log");
        SKYLIB_LOG(indent + "{");

        maybe<Package_Location_t*> location = Location();
        if (location) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "location:");
            location->Log(indent + SKYLIB_TAB + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "location: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}
