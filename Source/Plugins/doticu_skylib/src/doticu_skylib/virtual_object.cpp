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

        return Handle_t(get_handle(this));
    }

    Variable_t* Object_t::Variables()
    {
        return reinterpret_cast<Variable_t*>(this + 1);
    }

    Variable_t* Object_t::Variable(String_t variable_name)
    {
        maybe<Class_t*> v_class = this->v_class;
        maybe<size_t> variable_idx = none<size_t>();
        size_t variable_offset = 0;
        while (v_class) {
            if (variable_idx.Has_Value()) {
                variable_offset += v_class->Count_Variable_Infos();
            } else {
                variable_idx = v_class->Variable_Index(variable_name);
            }
            v_class = v_class->parent != v_class ? v_class->parent : nullptr;
        }

        if (variable_idx.Has_Value()) {
            return Variables() + variable_offset + variable_idx.Value();
        } else {
            return nullptr;
        }
    }

    Variable_t* Object_t::Property(String_t property_name)
    {
        maybe<Class_t*> v_class = this->v_class;
        maybe<size_t> property_idx = none<size_t>();
        size_t property_offset = 0;
        while (v_class) {
            if (property_idx.Has_Value()) {
                property_offset += v_class->Count_Variable_Infos(); // or v_class->Count_Property_Infos()?
            } else {
                property_idx = v_class->Property_Index(property_name);
            }
            v_class = v_class->parent != v_class ? v_class->parent : nullptr;
        }

        if (property_idx.Has_Value()) {
            return Variables() + property_offset + property_idx.Value();
        } else {
            return nullptr;
        }
    }

    void Object_t::Log_Variables()
    {
        SKYLIB_LOG("Logging Object Variables: %s", v_class->name);
        Variable_Info_t* variables_infos = v_class->Variable_Infos();
        for (size_t idx = 0, size = v_class->Count_Variable_Infos(); idx < size; idx += 1) {
            Variable_t& variable = Variables()[idx];
            Variable_Info_t& variable_info = variables_infos[idx];
            SKYLIB_LOG("Variable: %s", variable_info.name);
            if (variable_info.type.Is_Int()) {
                SKYLIB_LOG("    type: %s, val: %i\n", variable_info.type.To_String(), variable.data.i);
            } else if (variable_info.type.Is_String()) {
                SKYLIB_LOG("    type: %s, val: %s\n", variable_info.type.To_String(), variable.data.str);
            } else {
                SKYLIB_LOG("    type: %s, val: %p\n", variable_info.type.To_String(), variable.data.ptr);
            }
        }
    }

}}
