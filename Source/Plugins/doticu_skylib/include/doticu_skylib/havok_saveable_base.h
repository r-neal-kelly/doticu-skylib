/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_reference_base.h"

namespace doticu_skylib {

    class Havok_Saveable_Base_t :       // bhkSerializable
        public Havok_Reference_Base_t   // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E1AE50, // 685161
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Havok_Saveable_Base_t(); // 00

    public:
        void* unk_18; // 18
    };
    STATIC_ASSERT(sizeof(Havok_Saveable_Base_t) == 0x20);

}
