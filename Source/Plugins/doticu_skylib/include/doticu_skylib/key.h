/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/misc.h"

namespace doticu_skylib {

    class Key_t :       // TESKey
        public Misc_t   // 000
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::KEY,
        };

        static constexpr const char* SCRIPT_NAME = "Key";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E136A8, // 513893
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Key_t(); // 00
    };
    STATIC_ASSERT(sizeof(Key_t) == 0x100);

}
