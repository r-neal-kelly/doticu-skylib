/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/virtual_class.h"
#include "doticu_skylib/virtual_object.h"
#include "doticu_skylib/virtual_machine.h"

namespace doticu_skylib { namespace Virtual {

    void Object_t::Destroy()
    {
        static auto destroy = reinterpret_cast
            <void(*)(Object_t*)>
            (RelocationManager::s_baseAddr + static_cast<Word_t>(Offset_e::DESTROY));
        destroy(this);
    }

    void Object_t::Increment_Lock()
    {
        static auto increment_lock = reinterpret_cast
            <void(*)(Object_t*)>
            (RelocationManager::s_baseAddr + static_cast<Word_t>(Offset_e::INCREMENT_LOCK));
        increment_lock(this);
    }

    u32 Object_t::Decrement_Lock()
    {
        static auto decrement_lock = reinterpret_cast
            <u32(*)(Object_t*)>
            (RelocationManager::s_baseAddr + static_cast<Word_t>(Offset_e::DECREMENT_LOCK));
        return decrement_lock(this);
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

}}
