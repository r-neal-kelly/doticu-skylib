/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ni_object.h"

namespace doticu_skylib {

    class NI_Texture_Set_t :    // BSTextureSet
        public NI_Object_t      // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E1D6D8, // 685302
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~NI_Texture_Set_t(); // 00
    };
    STATIC_ASSERT(sizeof(NI_Texture_Set_t) == 0x10);

}
