/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_object.h"

namespace doticu_skylib {

    class Havok_Reference_t :   // hkReferencedObject
        public Havok_Object_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E1A1A0, // 685129
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Havok_Reference_t(); // 0

    public:
        u16             unk_08;             // 08
        volatile s16    reference_count;    // 0A
        u32             pad_0C;             // 0C
    };
    STATIC_ASSERT(sizeof(Havok_Reference_t) == 0x10);

}
