/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/ni_object.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class NI_Extra_t;

    class NI_Extras_t :     // NiObjectNET
        public NI_Object_t  // 00
    {
    public:
        virtual ~NI_Extras_t(); // 00

    public:
        String_t                    extras_name;        // 10
        void*                       time_controller;    // 18
        maybe<maybe<NI_Extra_t*>*>  extras;             // 20
        u16                         extra_count;        // 28
        u16                         max_count;          // 2A
        u32                         pad_2C;             // 2C

    public:
        Vector_t<some<NI_Extra_t*>> Extras();
        void                        Extras(Vector_t<some<NI_Extra_t*>>& results);
    };
    STATIC_ASSERT(sizeof(NI_Extras_t) == 0x30);

}
