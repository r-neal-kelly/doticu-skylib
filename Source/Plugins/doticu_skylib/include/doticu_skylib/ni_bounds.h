/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ni_point.h"

namespace doticu_skylib {

    class NI_Bounds_t // NiBound
    {
    public:
        NI_Point_3_t    center; // 0
        Float_t         radius; // C
    };
    STATIC_ASSERT(sizeof(NI_Bounds_t) == 0x10);

}
