/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_script_type.h"

#include "doticu_skylib/virtual.h"

namespace doticu_skylib { namespace Virtual {

    class Handle_t
    {
    public:
        Raw_Handle_t raw_handle = 0;

    public:
        template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t> = true>
        Handle_t(Scriptable_t scriptable);
        explicit Handle_t(Raw_Handle_t raw_handle);
        Handle_t();

    public:
        Bool_t Is_Valid();
        Bool_t Has_Script_Type(some<Script_Type_e> script_type);
        template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t> = true>
        Scriptable_t Resolve();

    public:
        operator Raw_Handle_t();
    };
    STATIC_ASSERT(sizeof(Handle_t) == 0x8);

}}

#include "doticu_skylib/virtual_policy.h"

namespace doticu_skylib { namespace Virtual {

    template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t>>
    Handle_t::Handle_t(Scriptable_t scriptable)
    {
        if (scriptable) {
            some<Script_Type_e> script_type = Script_Type_e::From<Scriptable_t>();
            raw_handle = Handle_Policy_t::Self()->Handle(script_type().Raw(), scriptable);
        } else {
            raw_handle = Handle_Policy_t::Self()->Invalid_Handle();
        }
    }

    template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t>>
    Scriptable_t Handle_t::Resolve()
    {
        some<Script_Type_e> script_type = Script_Type_e::From<Scriptable_t>();
        if (Is_Valid() && Has_Script_Type(script_type)) {
            return static_cast<Scriptable_t>
                (Handle_Policy_t::Self()->Resolve(script_type().Raw(), raw_handle));
        } else {
            return nullptr;
        }
    }

}}
