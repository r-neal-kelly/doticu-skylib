/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"

#include "doticu_skylib/game.h"
#include "doticu_skylib/memory.h"
#include "doticu_skylib/script.h"

namespace doticu_skylib {

    void Script_t::Command(some<const char*> command)
    {
        SKYLIB_ASSERT_SOME(command);

        size_t length = CString_t::Length(command(), true);
        if (length > 0) {
            Allocate_Command(length);
            memcpy(text, command(), length);
        }
    }

    void Script_t::Allocate_Command(size_t byte_count)
    {
        Deallocate_Command();

        maybe<Byte_t*> bytes = Memory_t::Self()->Allocate(byte_count);
        SKYLIB_ASSERT(bytes);
        text = reinterpret_cast<char*>(bytes());
    }

    void Script_t::Deallocate_Command()
    {
        if (text) {
            Memory_t::Self()->Deallocate(reinterpret_cast<Byte_t*>(text));
            text = nullptr;
        }
    }

    void Script_t::Execute(Reference_t* reference, Compiler_e compiler_e)
    {
        class Compiler_t
        {
        public:
        };

        static auto execute = reinterpret_cast
            <void(*)(Script_t*, Compiler_t*, Compiler_e::value_type, Reference_t*)>
            (Game_t::Base_Address() + Offset_e::EXECUTE);

        Compiler_t compiler;
        execute(this, &compiler, compiler_e, reference);
    }

}
