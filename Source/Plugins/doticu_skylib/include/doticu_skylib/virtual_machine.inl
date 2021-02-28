/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_object.h"

namespace doticu_skylib { namespace Virtual {

    template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t>>
    inline Bool_t Machine_t::Ready_Scriptable(some<Scriptable_t> scriptable)
    {
        SKYLIB_ASSERT_SOME(scriptable);
        return !!Object_t::Find_Or_Create(scriptable(), true);
    }

}}
