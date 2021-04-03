/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/dispelled_magic.h"
#include "doticu_skylib/magic_base.h"

namespace doticu_skylib {

    void Dispelled_Magic_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Dispelled_Magic_t::Log");
        SKYLIB_LOG(indent + "{");

        if (this->magic_base) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "magic_base:");
            this->magic_base->Log(indent + SKYLIB_TAB + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "magic_base: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}
