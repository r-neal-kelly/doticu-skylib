/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/const_actors.h"
#include "doticu_skylib/cstring.h"
#include "doticu_skylib/form_factory.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/memory.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/quest.h"
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

    void Script_t::operator delete(void* bytes)
    {
        SKYLIB_ASSERT(bytes);
        Destroy(static_cast<Script_t*>(bytes));
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

    void Script_t::Execute(maybe<Reference_t*> reference, Compiler_e compiler_e)
    {
        class Compiler_t
        {
        public:
        };

        static auto execute = reinterpret_cast
            <void(*)(Script_t*, Compiler_t*, Compiler_e::value_type, Reference_t*)>
            (Game_t::Base_Address() + Offset_e::EXECUTE);

        static some<Player_t*> player = Player_t::Self();

        if (!reference) {
            reference = player();
        }

        Compiler_t compiler;
        execute(this, &compiler, compiler_e, reference());
    }

    void Script_t::Console_Activate(some<Reference_t*> self, some<Reference_t*> activator, Bool_t only_default_event)
    {
        SKYLIB_ASSERT_SOME(self);
        SKYLIB_ASSERT_SOME(activator);

        if (self->Is_Valid() && activator->Is_Valid()) {
            Command(std::string("Activate ") + activator->Form_ID_String() + " " + (only_default_event ? "1" : "0"));
            Execute(self);
        }
    }

    void Script_t::Console_Add_Item(some<Reference_t*> self, some<Form_t*> item, s16 delta)
    {
        SKYLIB_ASSERT_SOME(self);
        SKYLIB_ASSERT_SOME(item);

        if (self->Is_Valid()) {
            Command(std::string("AddItem ") + item->Form_ID_String() + " " + std::to_string(delta));
            Execute(self);
        }
    }

    void Script_t::Console_Remove_Item(some<Reference_t*> self, some<Form_t*> item, s16 delta)
    {
        SKYLIB_ASSERT_SOME(self);
        SKYLIB_ASSERT_SOME(item);

        if (self->Is_Valid()) {
            Command(std::string("RemoveItem ") + item->Form_ID_String() + " " + std::to_string(delta));
            Execute(self);
        }
    }

    void Script_t::Console_Open_Container(some<Reference_t*> self)
    {
        SKYLIB_ASSERT_SOME(self);

        maybe<Actor_t*> actor = self->As_Actor();
        if (actor) {
            Console_Open_Container(actor(), true);
        } else {
            Console_Activate(self, Const::Actor::Player(), false);
        }
    }

    void Script_t::Console_Open_Container(some<Actor_t*> self, Bool_t allow_non_teammates)
    {
        SKYLIB_ASSERT_SOME(self);

        if (self->Is_Valid()) {
            Command(std::string("OpenActorContainer ") + (allow_non_teammates ? "1" : "0"));
            Execute(self());
        }
    }

    void Script_t::Console_Is_Objective_Completed(some<Quest_t*> self, u16 index, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(self);

        if (self->Is_Valid()) {
            Command(
                std::string("SetObjectiveCompleted ") +
                self->form_id.As_String() + " " +
                std::to_string(index) + " " +
                (value ? "1" : "0")
            );
            Execute(none<Reference_t*>());
        }
    }

    void Script_t::Console_Is_Objective_Displayed(some<Quest_t*> self, u16 index, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(self);

        if (self->Is_Valid()) {
            Command(
                std::string("SetObjectiveDisplayed ") +
                self->form_id.As_String() + " " +
                std::to_string(index) + " " +
                (value ? "1" : "0")
            );
            Execute(none<Reference_t*>());
        }
    }

}
