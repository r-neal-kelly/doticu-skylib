/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/form_factory.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/memory.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/script.h"

namespace doticu_skylib {

    some<Script_t*> Script_t::Create()
    {
        static some<Form_Factory_i*> script_factory = Form_Factory_i::Form_Factory(Form_Type_e(SCRIPT_TYPE));
        SKYLIB_ASSERT_SOME(script_factory);

        return static_cast<Script_t*>(script_factory->Create());
    }

    void Script_t::Destroy(some<Script_t*> script)
    {
        SKYLIB_ASSERT_SOME(script);

        script->Deallocate_Command();
        script->~Script_t();
        Game_t::Deallocate<Script_t>(script);
    }

    void Script_t::Allocate_Command(size_t byte_count)
    {
        Deallocate_Command();

        maybe<Byte_t*> bytes = Memory_t::Self()->Allocate(byte_count);
        SKYLIB_ASSERT(bytes);
        this->text = reinterpret_cast<char*>(bytes());
    }

    void Script_t::Deallocate_Command()
    {
        if (this->text) {
            Memory_t::Self()->Deallocate(reinterpret_cast<Byte_t*>(this->text()));
            this->text = nullptr;
        }
    }

    some<const char*> Script_t::Command()
    {
        if (this->text) {
            return this->text();
        } else {
            return "";
        }
    }

    void Script_t::Command(const char* command)
    {
        if (!command) {
            command = "";
        }

        size_t length = CString_t::Length(command, true);
        if (length > 0) {
            Allocate_Command(length);
            memcpy(this->text(), command, length);
        }
    }

    void Script_t::Command(std::string command)
    {
        Command(command.c_str());
    }

    void Script_t::Execute(some<Reference_t*> reference, Compiler_e compiler_e)
    {
        class Compiler_t
        {
        public:
        };

        static auto execute = reinterpret_cast
            <void(*)(Script_t*, Compiler_t*, Compiler_e::value_type, Reference_t*)>
            (Game_t::Base_Address() + Offset_e::EXECUTE);

        SKYLIB_ASSERT_SOME(reference);

        Compiler_t compiler;
        execute(this, &compiler, compiler_e, reference());
    }

    void Script_t::Console_Add_Item(some<Reference_t*> reference, some<Form_t*> item, s16 delta)
    {
        SKYLIB_ASSERT_SOME(reference);
        SKYLIB_ASSERT_SOME(item);

        if (reference->Is_Valid()) {
            Command(std::string("AddItem ") + item->Form_ID_String() + " " + std::to_string(delta));
            Execute(reference);
        }
    }

}
