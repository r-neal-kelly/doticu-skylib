/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Form_t;

    class Description_c :   // TESDescription
        public Form_Data_c  // 00
    {
    public:
        class Offset_e :
            Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                GET = 0x00190480,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Description_c(); // 0

    public:
        u32 description_offset;     // 8
        u32 description_text_id;    // C

    public:
        DString_t   Description(some<const Form_t*> parent, u32 sub_type = 'DESC') const;
        void        Description(some<const Form_t*> parent, u32 sub_type, DString_t& result) const;
    };
    STATIC_ASSERT(sizeof(Description_c) == 0x10);

}
