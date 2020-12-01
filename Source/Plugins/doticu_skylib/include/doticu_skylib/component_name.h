/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Name_c : public Form_Data_c // TESFullName
    {
    public:
        virtual             ~Name_c();      // 00

        virtual u32         Name_Length();  // 04
        virtual const char* Name();         // 05

        String_t name; // 8
    };
    STATIC_ASSERT(sizeof(Name_c) == 0x10);

}
