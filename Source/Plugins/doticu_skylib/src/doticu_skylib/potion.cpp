/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/potion.h"

namespace doticu_skylib {

    void Potion_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Potion_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "component_name: %s", Component_Name());

        SKYLIB_LOG(indent + "}");
    }

}
