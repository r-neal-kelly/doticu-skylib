/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ni_extra.h"
#include "doticu_skylib/ni_point.h"

namespace doticu_skylib {

    class NI_Extra_Bounds_t :   // BSBound
        public NI_Extra_t       // 00
    {
    public:
        virtual ~NI_Extra_Bounds_t(); // 00

    public:
        NI_Point_3_t    center; // 18
        NI_Point_3_t    bounds; // 24

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(NI_Extra_Bounds_t) == 0x30);

}
