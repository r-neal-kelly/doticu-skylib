/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/component_texture.h"
#include "doticu_skylib/enum_texture_set_flags.h"
#include "doticu_skylib/enum_texture_type.h"
#include "doticu_skylib/ni_texture_set.h"

namespace doticu_skylib {

    class Texture_Set_t :       // BGSTextureSet
        public Bound_Object_t,  // 000
        public NI_Texture_Set_t // 030
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::TEXTURE_SET,
        };

        static constexpr const char* SCRIPT_NAME = "TextureSet";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E15A08, // 513953
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Texture_Set_t(); // 0

    public:
        Texture_c           textures[Texture_Type_e::_TOTAL_];  // 040
        void*               decal_data;                         // 0C0
        Texture_Set_Flags_e texture_set_flags;                  // 0C8
        u16                 pad_0CA;                            // 0CA
        Byte_t              unk_0CC[0x60];                      // 0CC
        u32                 pad_12C;                            // 12C
    };
    STATIC_ASSERT(sizeof(Texture_Set_t) == 0x130);

}
