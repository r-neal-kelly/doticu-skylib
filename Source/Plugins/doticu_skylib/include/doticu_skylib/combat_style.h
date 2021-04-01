/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form.h"

namespace doticu_skylib {

    class Combat_Style_t :  // TESCombatStyle
        public Form_t       // 00
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::COMBAT_STYLE,
        };

        static constexpr const char* SCRIPT_NAME = "CombatStyle";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E138C8, // 513907
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Combat_Style_t(); // 00

    public:
        Byte_t  data_20[0x80];  // 20
    };
    STATIC_ASSERT(sizeof(Combat_Style_t) == 0xA0);

}
