/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/interface.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/enum_alias_fill.h"
#include "doticu_skylib/enum_alias_flags.h"

#include "doticu_skylib/alias_id.h"
#include "doticu_skylib/script_type.h"

namespace doticu_skylib {

    class Form_t;
    class Mod_t;
    class Quest_t;
    class Reference_t;

    namespace Virtual {

        class Callback_i;

    }

    class Alias_Base_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ALIAS_BASE,
        };

    public:
        virtual             ~Alias_Base_t();    // 0
        virtual Bool_t      _1(Mod_t* mod);     // 1
        virtual void        _2(Form_t* form);   // 2
        virtual String_t    Type();             // 3

    public:
        String_t        name;       // 08
        Quest_t*        quest;      // 10
        Alias_ID_t      id;         // 18
        Alias_Flags_e   flags;      // 1C
        Alias_Fill_e    fill_type;  // 20
        u16             pad_22;     // 22
        u32             pad_24;     // 24

    public:
        void Ready_Virtual_Object();

        void Fill(some<Reference_t*> reference, maybe<Virtual::Callback_i*> vcallback = nullptr);
        void Unfill(maybe<Virtual::Callback_i*> vcallback = nullptr);
        void Reference(some<Virtual::Callback_i*> vcallback);
        void Reference(some<Callback_i<Reference_t*>*> ucallback);
    };
    STATIC_ASSERT(sizeof(Alias_Base_t) == 0x28);

}
