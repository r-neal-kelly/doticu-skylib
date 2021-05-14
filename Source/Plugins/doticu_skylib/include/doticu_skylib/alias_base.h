/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/alias_id.h"
#include "doticu_skylib/enum_alias_base_flags.h"
#include "doticu_skylib/enum_alias_fill.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"
#include "doticu_skylib/unique.h"

namespace doticu_skylib {

    class Alias_Reference_t;
    class Form_t;
    class Mod_t;
    class Quest_t;
    class Reference_t;

    namespace Virtual {

        class Callback_i;

    }

    class Alias_Base_t // BGSBaseAlias
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ALIAS_BASE,
        };

        static constexpr const char* SCRIPT_NAME = "Alias";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI                        = 0x01E1ED30, // 685384

                MAYBE_CLEAR_NAME_ON_REMOVE  = 0x00111730, // 11510
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual             ~Alias_Base_t();    // 0
        virtual Bool_t      _1(Mod_t* mod);     // 1
        virtual void        _2(Form_t* form);   // 2
        virtual String_t    Get_Type();         // 3

    public:
        String_t            name;               // 08
        maybe<Quest_t*>     quest;              // 10
        Alias_ID_t          id;                 // 18
        Alias_Base_Flags_e  alias_base_flags;   // 1C
        Alias_Fill_e        fill_type;          // 20
        u16                 pad_22;             // 22
        u32                 pad_24;             // 24

    public:
        Bool_t                      Is_Alias_Reference();
        maybe<Alias_Reference_t*>   As_Alias_Reference();

        Bool_t                      Is_Protected();
        void                        Is_Protected(Bool_t value);
        Bool_t                      Is_Essential();
        void                        Is_Essential(Bool_t value);
        Bool_t                      Is_Quest_Item() const;
        void                        Is_Quest_Item(Bool_t value);
        Bool_t                      Do_Clear_Name_On_Remove() const;
        void                        Do_Clear_Name_On_Remove(Bool_t value);
        Bool_t                      Do_Store_Name() const;
        void                        Do_Store_Name(Bool_t value);
    };
    STATIC_ASSERT(sizeof(Alias_Base_t) == 0x28);

}
