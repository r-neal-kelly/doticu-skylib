/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/reference_handle.h"
#include "doticu_skylib/unique.h"

namespace doticu_skylib {

    class Alias_Reference_t :   // BGSRefAlias
        public Alias_Base_t     // 00
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ALIAS_REFERENCE,
        };

        static constexpr const char* SCRIPT_NAME = "ReferenceAlias";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E1F0C0, // 685398
            };
            using Enum_t::Enum_t;
        };

    public:
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
        static void Unfill(Vector_t<some<Alias_Reference_t*>>&& aliases, maybe<unique<Callback_i<>>> callback);

    public:
        virtual             ~Alias_Reference_t();       // 0
        virtual Bool_t      _1(Mod_t* mod) override;    // 1
        virtual void        _2(Form_t* form) override;  // 2
        virtual String_t    Get_Type() override;        // 3

    public:
        Fill_u  fill;       // 28
        void*   conditions; // 40

    public:
        void Fill(some<Reference_t*> reference, maybe<Virtual::Callback_i*> v_callback);    // ForceRefTo
        void Fill(some<Reference_t*> reference, maybe<unique<Callback_i<>>> callback);

        void Unfill(maybe<Virtual::Callback_i*> v_callback);                                // Clear
        void Unfill(maybe<unique<Callback_i<>>> callback);

        void To_Reference(some<Virtual::Callback_i*> v_callback);                           // GetReference
        void To_Reference(some<unique<Callback_i<maybe<Reference_t*>>>> callback);
    };
    STATIC_ASSERT(sizeof(Alias_Reference_t) == 0x48);

}
