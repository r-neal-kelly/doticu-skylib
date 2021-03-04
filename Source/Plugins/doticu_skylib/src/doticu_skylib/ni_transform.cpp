/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ni_transform.h"

namespace doticu_skylib {

    void NI_Transform_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "NI_Transform_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "rotation:");
        this->rotation.Log(indent + SKYLIB_TAB + SKYLIB_TAB);

        SKYLIB_LOG(indent + SKYLIB_TAB + "translation:");
        this->translation.Log(indent + SKYLIB_TAB + SKYLIB_TAB);

        SKYLIB_LOG(indent + SKYLIB_TAB + "scale: %.8f", this->scale);

        SKYLIB_LOG(indent + "}");
    }

}
