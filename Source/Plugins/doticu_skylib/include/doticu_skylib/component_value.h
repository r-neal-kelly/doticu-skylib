/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Value_c :         // TESValueForm
        public Form_Data_c  // 00
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E118F0, // 513880
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Value_c(); // 0

    public:
        s32 value;  // 08
        u32 pad_0C; // 0C
    };
    STATIC_ASSERT(sizeof(Value_c) == 0x10);

}
