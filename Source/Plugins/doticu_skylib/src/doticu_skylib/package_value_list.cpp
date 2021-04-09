/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value_list.h"

namespace doticu_skylib {

    void Package_Value_List_t::Log(std::string indent) const
    {
        SKYLIB_ASSERT(Is_List());

        SKYLIB_LOG(indent + "Package_Value_List_t::Log");
        SKYLIB_LOG(indent + "{");



        SKYLIB_LOG(indent + "}");
    }

}
