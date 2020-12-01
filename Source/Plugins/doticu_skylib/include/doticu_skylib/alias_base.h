/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/alias_id.h"
#include "doticu_skylib/form_type.h"

namespace doticu_skylib {

    class Form_t;
    class Mod_t;
    class Quest_t;

    class Alias_Flags_e : public Enum_t<u32>
    {
    public:
        enum : u32
        {
            // ...
            IS_ESSENTIAL    = 1 << 6,
            // ...
            IS_PROTECTED    = 1 << 10,
            // ...
        };
        using Enum_t::Enum_t;
    };

    class Alias_Fill_Type_e : public Enum_t<u16>
    {
    public:
        enum : u16
        {
            CONDITION   = 0,
            FORCED      = 1,
            // ...
        };
        using Enum_t::Enum_t;
    };

    class Alias_Base_t
    {
    public:
        enum
        {
            FORM_TYPE   = Form_Type_e::ALIAS_BASE,
            kTypeID     = FORM_TYPE,
        };

    public:
        virtual             ~Alias_Base_t();    // 0
        virtual Bool_t      _1(Mod_t* mod);     // 1
        virtual void        _2(Form_t* form);   // 2
        virtual String_t    Type();             // 3

        String_t            name;       // 08
        Quest_t*            quest;      // 10
        Alias_ID_t          id;         // 18
        Alias_Flags_e       flags;      // 1C
        Alias_Fill_Type_e   fill_type;  // 20
        u16                 pad_22;     // 22
        u32                 pad_24;     // 24

        void Log();
    };
    STATIC_ASSERT(sizeof(Alias_Base_t) == 0x28);

}
