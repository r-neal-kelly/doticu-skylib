/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_extra_text_display_type.h"
#include "doticu_skylib/extra_data.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"
#include "doticu_skylib/temper_level.h"

namespace doticu_skylib {

    class Message_t;
    class Quest_t;

    class Extra_Text_Display_t :    // ExtraTextDisplayData
        public Extra_Data_t         // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::TEXT_DISPLAY,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                V_TABLE     = 0x0152CAE0, // 229625

                SET_NAME    = 0x0013C870, // 12628
            };
            using Enum_t::Enum_t;
        };

        union Conditional_u
        {
        public:
            Extra_Text_Display_Type_e   type;
            u32                         owner_instance;

        public:
            Conditional_u();
            ~Conditional_u();
        };
        STATIC_ASSERT(sizeof(Conditional_u) == 0x4);

    public:
        static some<Extra_Text_Display_t*>  Create();
        static some<Extra_Text_Display_t*>  Create(const Extra_Text_Display_t& other);
        static void                         Destroy(some<Extra_Text_Display_t*> x_text_display);

    public:
        virtual ~Extra_Text_Display_t(); // 0

    public:
        String_t            name;           // 10
        maybe<Message_t*>   message;        // 18
        maybe<Quest_t*>     owner;          // 20
        Conditional_u       conditional;    // 28
        Temper_Level_t      temper_level;   // 2C
        u16                 name_length;    // 30
        u16                 pad_32;         // 32
        u32                 pad_34;         // 34

    public:
        void Name(some<const char*> name, Bool_t do_force);

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Extra_Text_Display_t) == 0x38);

}
