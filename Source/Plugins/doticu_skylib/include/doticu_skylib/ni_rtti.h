/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class NI_RTTI_t // NiRTTI
    {
    public:
        maybe<const char*>  name;       // 0
        maybe<NI_RTTI_t*>   base_rtti;  // 8
    };
    STATIC_ASSERT(sizeof(NI_RTTI_t) == 0x10);

}
