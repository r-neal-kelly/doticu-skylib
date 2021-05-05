/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ni_point.h"

namespace doticu_skylib {

    NI_Point_3_t::NI_Point_3_t() :
        x(0.0), y(0.0), z(0.0)
    {
    }

    void NI_Point_3_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "NI_Point_3_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "x: %16.8f", this->x);
        SKYLIB_LOG(indent + SKYLIB_TAB + "y: %16.8f", this->y);
        SKYLIB_LOG(indent + SKYLIB_TAB + "z: %16.8f", this->z);

        SKYLIB_LOG(indent + "}");
    }

}
