/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Quest_t;

    class Alias_Base_t {
    public:
        enum {
            kTypeID = kFormType_Alias
        };

        enum Flags : UInt32 {
            // ...
            IS_ESSENTIAL = 1 << 6,
            // ...
            IS_PROTECTED = 1 << 10,
            // ...
        };

        enum Fill_Types : UInt16 {
            CONDITION_FILL = 0,
            FORCED_FILL = 1
            // ...
        };

        virtual ~Alias_Base_t(); // 00
        virtual bool Load(File_t* file); // 01
        virtual void Item(Form_t* form); // 02
        virtual String_t Type(); // 03

        // void* _vtbl; // 00
        String_t name; // 08
        Quest_t* quest; // 10
        UInt32 id; // 18
        UInt32 flags; // 1C
        UInt16 fill_type; // 20
        UInt16 pad_22; // 22
        UInt32 pad_24; // 24

        void Log();
    };
    STATIC_ASSERT(sizeof(Alias_Base_t) == 0x28);

    class Alias_Reference_t : public Alias_Base_t {
    public:
        enum {
            kTypeID = kFormType_ReferenceAlias,
        };

        struct Forced_Fill {
            Reference_Handle_t ref_handle; // this never seems to be there...
        };
        STATIC_ASSERT(sizeof(Forced_Fill) == 0x4);

        union Fill_u {
            UInt64 padding[3];
            Forced_Fill forced;
        };
        STATIC_ASSERT(sizeof(Fill_u) == 0x18);

        virtual ~Alias_Reference_t(); // 00
        virtual bool Load(File_t* file) override; // 01
        virtual void Item(Form_t* form) override; // 02
        virtual String_t Type() override; // 03

        Fill_u fill; // 28
        void* conditions; // 40

        void Log();
    };
    STATIC_ASSERT(sizeof(Alias_Reference_t) == 0x48);

}
