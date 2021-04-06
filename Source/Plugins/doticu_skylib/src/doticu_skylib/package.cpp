/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/package.h"
#include "doticu_skylib/package_data.h"

namespace doticu_skylib {

    void Package_t::Log_Data(std::string indent) const
    {
        SKYLIB_LOG(indent + "Package_t::Log_Data");
        SKYLIB_LOG(indent + "{");

        if (this->data) {
            this->data->Log(indent + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "(none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}
