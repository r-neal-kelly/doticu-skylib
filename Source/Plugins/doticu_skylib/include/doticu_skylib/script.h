/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "doticu_skylib/form.h"

namespace doticu_skylib {

    class Reference_t;

    class Script_t :
        public Form_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::SCRIPT,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                EXECUTE = 0x002E75F0,
            };
            using Enum_t::Enum_t;
        };

        class Compiler_e : public Enum_t<u32>
        {
        public:
            enum : u32
            {
                DEFAULT,
                SYSTEM,
                DIALOGUE,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Script_t();

    public:
        u32     variable_count;         // 20
        u32     unk_24;                 // 24
        u32     unk_28;                 // 28
        u32     unk_2C;                 // 2C
        Bool_t  is_quest_script;        // 30
        Bool_t  is_magic_effect_script; // 31
        Bool_t  is_compiled;            // 32
        u8      pad_33;                 // 33
        u32     pad_34;                 // 34
        char*   text;                   // 38

    public:
        void Allocate_Command(size_t byte_count);
        void Deallocate_Command();

        void Command(some<const char*> command);
        void Execute(Reference_t* reference, Compiler_e compiler_e = Compiler_e::SYSTEM);
    };

}
