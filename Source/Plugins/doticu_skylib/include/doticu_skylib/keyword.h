/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Keyword_t :   // BGSKeyword
        public Form_t   // 00
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::KEYWORD,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E13958,
            };
            using Enum_t::Enum_t;
        };

    public:
        static Int_t Compare_Any_Names(Keyword_t** a, Keyword_t** b);

        static some<Keyword_t*> Vampire();

    public:
        virtual ~Keyword_t(); // 0

    public:
        String_t editor_id; // 20

    public:
        String_t Any_Name();
    };
    STATIC_ASSERT(sizeof(Keyword_t) == 0x28);

}
