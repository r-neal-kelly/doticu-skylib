/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"

#include "doticu_skylib/ni_extra_data.h"

namespace doticu_skylib {

    class NI_Extra_Bounds_t :   // BSBound
        public NI_Extra_Data_t  // 00
    {
    public:
        virtual ~NI_Extra_Bounds_t(); // 00

    public:
        f32_xyz center; // 18
        f32_xyz bounds; // 24

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(NI_Extra_Bounds_t) == 0x30);

}
