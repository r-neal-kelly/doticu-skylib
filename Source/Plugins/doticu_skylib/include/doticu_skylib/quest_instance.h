/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/alias_id.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/form_id.h"
#include "doticu_skylib/enum_global_type.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Form_t;
    class Global_t;

    class Quest_Instance_Alias_t    // BGSQuestInstanceText::StringData
    {
    public:
        Alias_ID_t  alias_id;       // 0
        Form_ID_t   data_form_id;   // 4 (these always seem to be of Object_t, base objects)

    public:
        maybe<Form_t*>  Data_Form();
    };
    STATIC_ASSERT(sizeof(Quest_Instance_Alias_t) == 0x8);

    class Quest_Instance_Global_t   // BGSQuestInstanceText::GlobalValueData
    {
    public:
        maybe<Global_t*>    global; // 00
        Float_t             value;  // 08
        u32                 pad_0C; // 0C

    public:
        Global_Type_e   Type();

        Bool_t          Is_Float();
        Bool_t          Is_Short();
        Bool_t          Is_Long();

        Float_t         Float();
        s16             Short();
        s32             Long();

        std::string     Float_String();
        std::string     Short_String();
        std::string     Long_String();
    };
    STATIC_ASSERT(sizeof(Quest_Instance_Global_t) == 0x10);

    class Quest_Instance_t  // BGSQuestInstanceText
    {
    public:
        u32                                 id;                 // 00
        u32                                 pad_04;             // 04
        Array_t<Quest_Instance_Alias_t>     aliases;            // 08
        Array_t<Quest_Instance_Global_t>    globals;            // 20
        u16                                 journal_stage;      // 38
        s8                                  journal_stage_item; // 3A
        u8                                  pad_3B;             // 3B
        u32                                 pad_3C;             // 3C

    public:
        maybe<Quest_Instance_Alias_t*>  Alias(some<Alias_ID_t> alias_id);
        maybe<Quest_Instance_Global_t*> Global(some<const char*> global_editor_id);
    };
    STATIC_ASSERT(sizeof(Quest_Instance_t) == 0x40);

}
