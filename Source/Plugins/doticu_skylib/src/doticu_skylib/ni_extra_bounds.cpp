/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/ni_extra_bounds.h"

namespace doticu_skylib {

    void NI_Extra_Bounds_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "NI_Extra_Bounds_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "center");
        SKYLIB_LOG(indent + SKYLIB_TAB + "{");
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "x: %f", this->center.x);
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "y: %f", this->center.y);
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "z: %f", this->center.z);
        SKYLIB_LOG(indent + SKYLIB_TAB + "}");

        SKYLIB_LOG(indent + SKYLIB_TAB + "bounds");
        SKYLIB_LOG(indent + SKYLIB_TAB + "{");
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "x: %f", this->bounds.x);
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "y: %f", this->bounds.y);
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "z: %f", this->bounds.z);
        SKYLIB_LOG(indent + SKYLIB_TAB + "}");

        SKYLIB_LOG(indent + "}");
    }

}
