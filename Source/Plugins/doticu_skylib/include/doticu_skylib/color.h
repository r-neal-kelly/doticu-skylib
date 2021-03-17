/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/enum_color_flags.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/form.h"

namespace doticu_skylib {

    class Color_t :     // BGSColorForm
        public Form_t,  // 00
        public Name_c   // 20
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::COLOR,
        };

        static constexpr const char* SCRIPT_NAME = "ColorForm";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E1BF28, // 513992
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Color_t(); // 0

    public:
        u8_rgba         rgba;           // 30
        Color_Flags_e   color_flags;    // 34
        u8              pad_35;         // 35
        u16             pad_36;         // 36
    };
    STATIC_ASSERT(sizeof(Color_t) == 0x38);

}
