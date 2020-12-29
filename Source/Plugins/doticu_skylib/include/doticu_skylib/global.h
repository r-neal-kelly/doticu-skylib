/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/string.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/script_type.h"

namespace doticu_skylib {

    class Global_Type_e : Enum_t<char>
    {
    public:
        enum : char
        {
            FLOAT   = 'f',
            SHORT   = 's',
            LONG    = 'l',
        };
        using Enum_t::Enum_t;
    };

    class Global_t : public Form_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::GLOBAL,
        };

    public:
        virtual ~Global_t();

        Dynamic_String_t    editor_id;  // 20
        Global_Type_e       type;       // 30
        u8                  pad_31;     // 31
        u16                 pad_32;     // 32
        Float_t             value;      // 34

        Bool_t  Bool();
        Float_t Float();
        u16     Short();
        u32     Long();

        void    Bool(Bool_t value);
        void    Float(Float_t value);
        void    Short(u16 value);
        void    Long(u32 value);
    };
    STATIC_ASSERT(sizeof(Global_t) == 0x38);

}
