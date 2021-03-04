/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/string.h"

#include "doticu_skylib/ni_object.h"

namespace doticu_skylib {

    class NI_Extra_t :      // NiExtraData
        public NI_Object_t  // 00
    {
    public:
        virtual ~NI_Extra_t(); // 00

    public:
        String_t extra_name; // 10

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(NI_Extra_t) == 0x18);

}
