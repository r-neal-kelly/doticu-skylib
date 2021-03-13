/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/enchantment.h"

namespace doticu_skylib {

    void Enchantment_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Enchantment_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "component_name: %s", Component_Name());

        SKYLIB_LOG(indent + "}");
    }

}
