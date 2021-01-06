/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_handle.h"
#include "doticu_skylib/virtual_machine.h"

namespace doticu_skylib { namespace Virtual {

    Handle_t::Handle_t(Raw_Handle_t raw_handle) :
        raw_handle(raw_handle)
    {
    }

    Handle_t::Handle_t() :
        raw_handle(Handle_Policy_t::Self()->Invalid_Handle())
    {
    }

    Bool_t Handle_t::Is_Valid()
    {
        return Handle_Policy_t::Self()->Is_Valid(*this);
    }

    Bool_t Handle_t::Has_Script_Type(some<Script_Type_e> script_type)
    {
        SKYLIB_ASSERT_SOME(script_type);
        return Handle_Policy_t::Self()->Has_Script_Type(script_type(), raw_handle);
    }

    Handle_t::operator Raw_Handle_t()
    {
        return raw_handle;
    }

}}
