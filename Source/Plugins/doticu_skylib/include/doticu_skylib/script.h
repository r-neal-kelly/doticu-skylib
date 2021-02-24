/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/forward_list.h"

namespace doticu_skylib {

    class Quest_t;
    class Reference_t;
    class Script_Object_t;
    class Script_Variable_t;

    class Script_t :    // Script
        public Form_t   // 00
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::SCRIPT,
        };

        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                EXECUTE = 0x002E75F0, // 21416
            };
            using Enum_t::Enum_t;
        };

        class Compiler_e :
            public Enum_t<u32>
        {
        public:
            enum enum_type : value_type
            {
                DEFAULT     = 0,
                SYSTEM      = 1,
                DIALOGUE    = 2,
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Script_t*>  Create();
        static void             Destroy(some<Script_t*> script);

    public:
        virtual ~Script_t(); // 0

    public:
        u32                                         variable_count;         // 20
        u32                                         unk_24;                 // 24
        u32                                         unk_28;                 // 28
        u32                                         unk_2C;                 // 2C
        Bool_t                                      is_quest_script;        // 30
        Bool_t                                      is_magic_effect_script; // 31
        Bool_t                                      is_compiled;            // 32
        u8                                          pad_33;                 // 33
        u32                                         pad_34;                 // 34
        maybe<char*>                                text;                   // 38
        void*                                       unk_40;                 // 40
        Float_t                                     profiler_timer;         // 48
        Float_t                                     quest_script_delay;     // 4C
        Float_t                                     unk_50;                 // 50
        u32                                         pad_54;                 // 54
        maybe<Quest_t*>                             quest;                  // 58
        Forward_List_t<maybe<Script_Object_t*>>     script_objects;         // 60
        Forward_List_t<maybe<Script_Variable_t*>>   script_variables;       // 70

    public:
        void                Allocate_Command(size_t byte_count);
        void                Deallocate_Command();

        some<const char*>   Command();
        void                Command(some<const char*> command);

        void                Execute(some<Reference_t*> reference, Compiler_e compiler_e = Compiler_e::SYSTEM);
    };
    STATIC_ASSERT(sizeof(Script_t) == 0x80);

}
