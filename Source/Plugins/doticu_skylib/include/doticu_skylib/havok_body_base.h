/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_saveable_base.h"

namespace doticu_skylib {

    class Havok_World_t;

    class Havok_Body_Base_t :           // bhkWorldObject
        public Havok_Saveable_Base_t    // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E17D40, // 513964
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Havok_Body_Base_t(); // 00

    public:
        maybe<Havok_World_t*> world; // 20
    };
    STATIC_ASSERT(sizeof(Havok_Body_Base_t) == 0x28);

}
