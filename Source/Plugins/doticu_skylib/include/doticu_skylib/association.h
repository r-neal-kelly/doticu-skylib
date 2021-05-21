/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_association_flags.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Association_t :   // BGSAssociationType
        public Form_t       // 00
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ASSOCIATION,
        };

        static constexpr const char* SCRIPT_NAME = "AssociationType";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E1E480, // 514000
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        String_t            male_parent;        // 20
        String_t            female_parent;      // 28
        String_t            male_child;         // 30
        String_t            female_child;       // 38
        Association_Flags_e association_flags;  // 40
        u32                 pad_44;             // 44
    };
    STATIC_ASSERT(sizeof(Association_t) == 0x48);

}
