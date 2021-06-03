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

        static constexpr const char* SCRIPT_NAME = "Keyword";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E13958, // 513911
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        static Int_t Compare_Any_Names(Keyword_t*& a, Keyword_t*& b);

    public:
        virtual ~Keyword_t(); // 0

    public:
        String_t editor_id; // 20

    public:
        String_t Any_Name();

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Keyword_t) == 0x28);

}
