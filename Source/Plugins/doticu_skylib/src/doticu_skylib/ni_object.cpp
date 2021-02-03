/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/ni_object.h"
#include "doticu_skylib/ni_rtti.h"

namespace doticu_skylib {

    void NI_Object_t::Log_RTTIs(std::string indent)
    {
        SKYLIB_LOG(indent + "NI_Object_t::Log_RTTIs");
        SKYLIB_LOG(indent + "{");

        for (NI_RTTI_t* it = Get_RTTI(); it; it = it->base_rtti() != it ? it->base_rtti() : nullptr) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "%s", it->name);
        }

        SKYLIB_LOG(indent + "}");
    }

}
