/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/script_type.h"

#include "doticu_skylib/virtual.h"

namespace doticu_skylib { namespace Virtual {

    class Handle_t {
    public:
        Raw_Handle_t raw_handle = 0;

        template <typename Scriptable_t>
        Handle_t(Scriptable_t* scriptable);
        Handle_t(Raw_Handle_t raw_handle);
        Handle_t();

        Bool_t Is_Valid();
        Bool_t Has_Script_Type(Script_Type_e script_type);

        operator Raw_Handle_t();
    };
    STATIC_ASSERT(sizeof(Handle_t) == 0x8);

}}

#include "doticu_skylib/virtual_policy.h"

namespace doticu_skylib { namespace Virtual {

    template <typename Scriptable_t>
    Handle_t::Handle_t(Scriptable_t* scriptable)
    {
        if (scriptable) {
            raw_handle = Handle_Policy_t::Self()->Handle(Scriptable_t::SCRIPT_TYPE, scriptable);
        } else {
            raw_handle = Handle_Policy_t::Self()->Invalid_Handle();
        }
    }

}}
