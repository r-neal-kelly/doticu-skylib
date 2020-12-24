/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/string.h"

#include "doticu_skylib/script_type.h"

#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_type.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib { namespace Virtual {

    struct Setting_Info_t {
        u64 unk_00; // 00
    };
    STATIC_ASSERT(sizeof(Setting_Info_t) == 0x8);

    struct Variable_Info_t {
        String_t name; // 00
        Type_e type; // 08
    };
    STATIC_ASSERT(sizeof(Variable_Info_t) == 0x10);

    struct Default_Info_t {
        u32 variable_idx; // 00
        u32 pad_04; // 04
        Variable_t variable; // 08
    };
    STATIC_ASSERT(sizeof(Default_Info_t) == 0x18);

    struct Property_Info_t {
        String_t name; // 00
        String_t parent_name; // 08
        String_t property_name; // 10
        Type_e type; // 18
        u32 flags_20; // 20
        u32 unk_24; // 24
        IFunction* getter; // 28
        IFunction* setter; // 30
        u32 auto_var_idx; // 38
        u32 flags_3C; // 3C
        String_t unk_40; // 40
    };
    STATIC_ASSERT(sizeof(Property_Info_t) == 0x48);

    class Class_t {
    public:
        static Class_t* Fetch(String_t class_name, Bool_t do_auto_decrement = false);
        static Class_t* Fetch(Script_Type_e script_type, Bool_t do_auto_decrement = false);

    public:
        u32 ref_count; // 00
        u32 pad_04; // 04
        String_t name; // 08
        Class_t* parent; // 10
        String_t unk_18; // 18
        u32 flags_20; // 20
        u32 flags_24; // 24
        u32 flags_28; // 28
        u32 pad_2C; // 2C
        u8* data; // 30

        size_t Count_Setting_Infos();
        size_t Count_Variable_Infos();
        size_t Count_Default_Infos();
        size_t Count_Property_Infos();

        Setting_Info_t* Setting_Infos();
        Variable_Info_t* Variable_Infos();
        Default_Info_t* Default_Infos();
        Property_Info_t* Property_Infos();

        Index_t Variable_Index(String_t variable_name);
        Index_t Property_Index(String_t property_name);
        Property_Info_t* Property_Info(String_t property_name);

        maybe<Script_Type_e> Script_Type();

        void Hold();
        void Free();

        void Log();
        //void Log_Setting_Infos();
        void Log_Variable_Infos();
        void Log_Default_Infos();
        void Log_Property_Infos();
    };
    STATIC_ASSERT(sizeof(Class_t) == 0x38);

}}
