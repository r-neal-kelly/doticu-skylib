/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"

#include "doticu_skylib/virtual_class.h"
#include "doticu_skylib/virtual_object.h"
#include "doticu_skylib/virtual_machine.h"

namespace doticu_skylib { namespace Virtual {

    void Object_t::Destroy()
    {
        static auto destroy = reinterpret_cast
            <void(*)(Object_t*)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::DESTROY));

        destroy(this);
    }

    void Object_t::Increment_Lock()
    {
        static auto increment_lock = reinterpret_cast
            <void(*)(Object_t*)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::INCREMENT_LOCK));

        increment_lock(this);
    }

    u32 Object_t::Decrement_Lock()
    {
        static auto decrement_lock = reinterpret_cast
            <u32(*)(Object_t*)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::DECREMENT_LOCK));

        return decrement_lock(this);
    }

    Handle_t Object_t::Handle()
    {
        static auto get_handle = reinterpret_cast
            <Raw_Handle_t(*)(Object_t*)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::GET_HANDLE));

        return get_handle(this);
    }

    Variable_t* Object_t::Variables()
    {
        return reinterpret_cast<Variable_t*>(this + 1);
    }

    Variable_t* Object_t::Variable(String_t variable_name)
    {
        Class_t* info = this->info;
        SInt64 idx = -1;
        SInt64 offset = 0;
        while (info) {
            if (idx < 0) {
                idx = info->Variable_Index(variable_name);
            } else {
                offset += info->Count_Variable_Infos();
            }
            info = info->parent != info ? info->parent : nullptr;
        }

        if (idx > -1) {
            return Variables() + offset + idx;
        } else {
            return nullptr;
        }
    }

    Variable_t* Object_t::Property(String_t property_name)
    {
        Class_t* info = this->info;
        SInt64 idx = -1;
        SInt64 offset = 0;
        while (info) {
            if (idx < 0) {
                idx = info->Property_Index(property_name);
            } else {
                offset += info->Count_Variable_Infos();
            }
            info = info->parent != info ? info->parent : nullptr;
        }

        if (idx > -1) {
            return Variables() + offset + idx;
        } else {
            return nullptr;
        }
    }

    void Object_t::Log_Variables()
    {
        _MESSAGE("Logging Object Variables: %s", info->name);
        Variable_Info_t* variables_infos = info->Variable_Infos();
        for (u64 idx = 0, size = info->Count_Variable_Infos(); idx < size; idx += 1) {
            Variable_t& variable = Variables()[idx];
            Variable_Info_t& info = variables_infos[idx];
            _MESSAGE("Variable: %s", info.name);
            if (info.type.Is_Int()) {
                _MESSAGE("    type: %s, val: %i\n", info.type.To_String(), variable.data.i);
            } else if (info.type.Is_String()) {
                _MESSAGE("    type: %s, val: %s\n", info.type.To_String(), variable.data.str);
            } else {
                _MESSAGE("    type: %s, val: %p\n", info.type.To_String(), variable.data.ptr);
            }
        }
    }

}}
