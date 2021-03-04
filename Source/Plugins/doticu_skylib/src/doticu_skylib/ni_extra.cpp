/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ni_extra.h"

namespace doticu_skylib {

    void NI_Extra_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "NI_3D_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "extra_name: %s", this->extra_name);

        SKYLIB_LOG(indent + "}");
    }

}
