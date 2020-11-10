/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form.h"
#include "doticu_skylib/papyrus.h"
#include "doticu_skylib/papyrus/type.h"
#include "doticu_skylib/papyrus/variable.h"

namespace doticu_skylib { namespace Papyrus {

    class Class_t {
    public:
        static Class_t* Fetch(String_t class_name, Bool_t do_auto_decrement = false);
        static Class_t* Fetch(Form_Type_t form_type, Bool_t do_auto_decrement = false);

        struct Setting_Info_t {
            UInt64 unk_00; // 00
        };
        STATIC_ASSERT(sizeof(Setting_Info_t) == 0x8);

        struct Variable_Info_t {
            String_t name; // 00
            Type_t type; // 08
        };
        STATIC_ASSERT(sizeof(Variable_Info_t) == 0x10);

        struct Default_Info_t {
            UInt32 variable_idx; // 00
            UInt32 pad_04; // 04
            Variable_t variable; // 08
        };
        STATIC_ASSERT(sizeof(Default_Info_t) == 0x18);

        struct Property_Info_t {
            String_t name; // 00
            String_t parent_name; // 08
            String_t property_name; // 10
            Type_t type; // 18
            UInt32 flags_20; // 20
            UInt32 unk_24; // 24
            IFunction* getter; // 28
            IFunction* setter; // 30
            UInt32 auto_var_idx; // 38
            UInt32 flags_3C; // 3C
            String_t unk_40; // 40
        };
        STATIC_ASSERT(sizeof(Property_Info_t) == 0x48);

        UInt32 ref_count; // 00
        UInt32 pad_04; // 04
        String_t name; // 08
        Class_t* parent; // 10
        String_t unk_18; // 18
        UInt32 flags_20; // 20
        UInt32 flags_24; // 24
        UInt32 flags_28; // 28
        UInt32 pad_2C; // 2C
        UInt8* data; // 30

        UInt64 Count_Setting_Infos();
        UInt64 Count_Variable_Infos();
        UInt64 Count_Default_Infos();
        UInt64 Count_Property_Infos();

        Setting_Info_t* Setting_Infos();
        Variable_Info_t* Variable_Infos();
        Default_Info_t* Default_Infos();
        Property_Info_t* Property_Infos();

        SInt64 Variable_Index(String_t variable_name);
        SInt64 Property_Index(String_t property_name);
        Property_Info_t* Property_Info(String_t property_name);

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
