/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/enum_extra_text_display_type.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Message_t;
    class Quest_t;

    class Text_Display_x : public Data_x // ExtraTextDisplayData
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::TEXT_DISPLAY,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE     = 0x0152CAE0, // 229625
                SET_NAME    = 0x0013C870, // 12628
            };
            using Enum_t::Enum_t;
        };

        union Conditional_u
        {
            Text_Display_Type_e type;
            u32                 owner_instance;
        };
        STATIC_ASSERT(sizeof(Conditional_u) == 0x4);

    public:
        virtual ~Text_Display_x();

    public:
        String_t        name;           // 10
        Message_t*      message;        // 18
        Quest_t*        owner;          // 20
        Conditional_u   conditional;    // 28
        Float_t         temper_health;  // 2C
        u16             custom_length;  // 30
        u16             pad_32;         // 32
        u32             pad_34;         // 34

    public:
        void Name(some<const char*> name, Bool_t do_force);

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Text_Display_x) == 0x38);

}
