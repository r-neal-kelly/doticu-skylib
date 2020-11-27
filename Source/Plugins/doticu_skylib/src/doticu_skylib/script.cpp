/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/script.h"

namespace doticu_skylib {

    void Script_t::Command(const char* command)
    {
        size_t length = CString_t::Length(command, true);
        if (length > 0) {
            if (text) {
                free(text);
            }
            text = static_cast<char*>(malloc(length));
            memcpy(text, command, length);
        }
    }

    void Script_t::Execute(Reference_t* reference, Compiler_e compiler_e)
    {
        class Compiler_t
        {
        public:
        };

        static auto execute = reinterpret_cast
            <void(*)(Script_t*, Compiler_t*, Compiler_e, Reference_t*)>
            (RelocationManager::s_baseAddr + Offset_e::EXECUTE);

        Compiler_t compiler;
        execute(this, &compiler, compiler_e, reference);
    }

}
