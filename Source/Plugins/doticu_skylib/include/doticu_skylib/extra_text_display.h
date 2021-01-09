/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/string.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Quest_t;

    class Text_Display_Type_e : public Enum_t<s32>
    {
    public:
        enum : value_type
        {
            DEFAULT = -1,
            CUSTOM  = -2,
        };
        using Enum_t::Enum_t;
    };

    // I would like to look at the data before sticking to this name.
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
                V_TABLE = 0x0152CAE0,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Text_Display_x();

    public:
        String_t            name;           // 10
        void*               message;        // 18
        Quest_t*            owner;          // 20
        Text_Display_Type_e type;           // 28
        Float_t             temper_health;  // 2C
        u16                 custom_length;  // 30
        u16                 pad_32;         // 32
        u32                 pad_34;         // 34

    public:
        void Rename(String_t name, Bool_t do_force);
    };
    STATIC_ASSERT(sizeof(Text_Display_x) == 0x38);

}
