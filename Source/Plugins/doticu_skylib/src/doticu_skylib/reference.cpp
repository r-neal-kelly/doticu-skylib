/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/worldspace.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/script.h"
#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.h"

namespace doticu_skylib {

    Int_t Reference_Count_t::Reference_Count()
    {
        return reference_count & 0x3FF;
    }

    Int_t Reference_Count_t::Increment_Reference()
    {
        return _InterlockedIncrement(static_cast<volatile u32*>(&reference_count)) & 0x3FF;
    }

    Int_t Reference_Count_t::Decrement_Reference()
    {
        Int_t count = _InterlockedDecrement(static_cast<volatile u32*>(&reference_count));
        if ((count & 0x3FF) == 0) {
            delete this; // not sure this is right. might want to call MarkForDelete through virtual machine script (as if console)
        }
        return count;
    }

    Reference_t* Reference_t::Create(Form_t* base, u32 count, Reference_t* at, Bool_t force_persist, Bool_t initially_disable)
    {
        static auto place_at_me = reinterpret_cast
            <Reference_t*(*)(Virtual::Machine_t*, Virtual::Stack_ID_t, Reference_t*, Form_t*, u32, Bool_t, Bool_t)>
            (RelocationManager::s_baseAddr + Offset_e::PLACE_AT_ME);
        return place_at_me(Virtual::Machine_t::Self(), 0, at, base, count, force_persist, initially_disable);
    }

    Bool_t Reference_t::Is_Persistent()
    {
        return (form_flags & Form_Flags_e::IS_PERSISTENT) != 0;
    }

    Bool_t Reference_t::Is_Temporary()
    {
        return !Is_Persistent();
    }

    const char* Reference_t::Name()
    {
        static auto get_name = reinterpret_cast
            <const char*(*)(Reference_t*)>
            (RelocationManager::s_baseAddr + static_cast<Word_t>(Offset_e::GET_NAME));
        return get_name(this);
    }

    String_t Reference_t::Any_Name()
    {
        const char* name = Name();
        if (!name || !name[0]) {
            name = Get_Editor_ID();
            if (!name || !name[0]) {
                return Form_ID_String();
            } else {
                return name;
            }
        } else {
            return name;
        }
    }

    Location_t* Reference_t::Location()
    {
        Cell_t* cell = Cell();
        if (cell) {
            return Cell()->Location();
        } else {
            return nullptr;
        }
    }

    Cell_t* Reference_t::Cell()
    {
        return parent_cell;
    }

    void Reference_t::Select_In_Console()
    {
        Form_Factory_i* script_factory = Form_Factory_i::Form_Factory(Form_Type_e::SCRIPT);

        if (Is_Valid()) {
            Script_t* script = static_cast<Script_t*>(script_factory->Create());
            SKYLIB_ASSERT(script);
            script->Command((std::string("prid ") + Form_ID_String().data).c_str());
            script->Execute(this);
            delete script;
        }
    }

    void Reference_t::Enable()
    {
        static Form_Factory_i* script_factory = Form_Factory_i::Form_Factory(Form_Type_e::SCRIPT);

        if (Is_Valid()) {
            Script_t* script = static_cast<Script_t*>(script_factory->Create());
            SKYLIB_ASSERT(script);
            script->Command("Enable");
            script->Execute(this);
            delete script;
        }
    }

    void Reference_t::Disable()
    {
        static Form_Factory_i* script_factory = Form_Factory_i::Form_Factory(Form_Type_e::SCRIPT);

        if (Is_Valid()) {
            Script_t* script = static_cast<Script_t*>(script_factory->Create());
            SKYLIB_ASSERT(script);
            script->Command("Disable");
            script->Execute(this);
            delete script;
        }
    }

    void Reference_t::Mark_For_Delete(Bool_t do_disable)
    {
        static Form_Factory_i* script_factory = Form_Factory_i::Form_Factory(Form_Type_e::SCRIPT);

        if (Is_Valid()) {
            Script_t* script = static_cast<Script_t*>(script_factory->Create());
            SKYLIB_ASSERT(script);
            if (do_disable) {
                script->Command("Disable");
                script->Execute(this);
            }
            if (Is_Persistent()) {
                script->Command("MarkForDelete");
                script->Execute(this);
            }
            delete script;
        }
    }

    void Reference_t::Delete(Virtual::Callback_i* vcallback)
    {
        Virtual::Machine_t::Self()->Call_Method(
            this,
            "ObjectReference",
            "Delete",
            nullptr,
            &vcallback
        );
    }

    /*void Reference_t::Delete_Persistent(Virtual::Callback_i* vcallback)
    {
        form_flags &= ~Form_Flags_e::IS_PERSISTENT;
        Delete(vcallback);
    }*/

}
