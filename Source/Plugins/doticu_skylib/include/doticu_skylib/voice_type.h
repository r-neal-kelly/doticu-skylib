/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_voice_type_flags.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Voice_Type_t :    // BGSVoiceType
        public Form_t       // 00
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::VOICE_TYPE,
        };

        static constexpr const char* SCRIPT_NAME = "VoiceType";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E14B68, // 513919
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Voice_Type_t(); // 0

    public:
        Voice_Type_Flags_e  voice_type_flags;   // 20
        u8                  pad_21;             // 21
        u16                 pad_22;             // 22
        u16                 pad_24;             // 24
        Dynamic_String_t    form_editor_id;     // 28
    };
    STATIC_ASSERT(sizeof(Voice_Type_t) == 0x38);

}
