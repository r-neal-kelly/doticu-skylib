/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Active_Magic_Effect_t // ActiveEffect
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ACTIVE_MAGIC_EFFECT,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E38CE0, // 514042
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Active_Magic_Effect_t(); // 0

    public:
        Byte_t data[0x88]; // 08
    };
    STATIC_ASSERT(sizeof(Active_Magic_Effect_t) == 0x90);

}
