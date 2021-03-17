/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_form_data.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Name_c :          // TESFullName
        public Form_Data_c  // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E10F00, // 513854
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual             ~Name_c();      // 00

        virtual u32         Name_Length();  // 04
        virtual const char* Name();         // 05

    public:
        String_t name; // 08
    };
    STATIC_ASSERT(sizeof(Name_c) == 0x10);

}
