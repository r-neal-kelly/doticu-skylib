/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/reference_handle.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Alias_Reference_t : public Alias_Base_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ALIAS_REFERENCE,
        };

        class Forced_Fill_t
        {
        public:
            Reference_Handle_t ref_handle; // only for static, never dynamic...
        };
        STATIC_ASSERT(sizeof(Forced_Fill_t) == 0x4);

        union Fill_u
        {
            u64             pad[3];
            Forced_Fill_t   forced;
        };
        STATIC_ASSERT(sizeof(Fill_u) == 0x18);

    public:
        virtual             ~Alias_Reference_t();               // 0
        virtual Bool_t      _1(Mod_t* mod)          override;   // 1
        virtual void        _2(Form_t* form)        override;   // 2
        virtual String_t    Type()                  override;   // 3

        Fill_u  fill;       // 28
        void*   conditions; // 40

        void Log();
    };
    STATIC_ASSERT(sizeof(Alias_Reference_t) == 0x48);

}
