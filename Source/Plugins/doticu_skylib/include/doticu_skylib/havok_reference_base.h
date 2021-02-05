/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

#include "doticu_skylib/ni_object.h"

namespace doticu_skylib {

    class Havok_Reference_t;

    class Havok_Reference_Base_t :  // bhkRefObject
        public NI_Object_t          // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E1AE78, // 685162
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual         ~Havok_Reference_Base_t();  // 00

        // Havok_Reference_Base_t
        virtual void    _25(void);                  // 25
        virtual void    _26(void);                  // 26

    public:
        maybe<Havok_Reference_t*> reference; // 10
    };
    STATIC_ASSERT(sizeof(Havok_Reference_Base_t) == 0x18);

}
