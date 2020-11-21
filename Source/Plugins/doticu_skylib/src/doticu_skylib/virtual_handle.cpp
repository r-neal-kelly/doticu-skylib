/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_handle.h"
#include "doticu_skylib/virtual_machine.h"

namespace doticu_skylib { namespace Virtual {

    Handle_t::Handle_t(void* form, Form_Type_e form_type)
    {
        if (form) {
            raw_handle = Handle_Policy_t::Self()->Handle(form_type, form);
        } else {
            raw_handle = Handle_Policy_t::Self()->Invalid_Handle();
        }
    }

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

    Bool_t Handle_t::Has_Form_Type(Form_Type_e form_type)
    {
        return Handle_Policy_t::Self()->Has_Form_Type(form_type, *this);
    }

    Handle_t::operator Raw_Handle_t()
    {
        return raw_handle;
    }

}}
