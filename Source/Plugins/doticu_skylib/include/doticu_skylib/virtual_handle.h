/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form_type.h"
#include "doticu_skylib/virtual.h"

namespace doticu_skylib { namespace Virtual {

    class Handle_t {
    public:
        Raw_Handle_t raw_handle = 0;

        template <typename Type>
        Handle_t(Type* form_or_alias);
        Handle_t(void* form, Form_Type_e form_type);
        Handle_t(Raw_Handle_t raw_handle);
        Handle_t();

        Bool_t Is_Valid();
        Bool_t Has_Form_Type(Form_Type_e form_type);

        operator Raw_Handle_t();
    };
    STATIC_ASSERT(sizeof(Handle_t) == 0x8);

}}

#include "doticu_skylib/virtual_policy.h"

namespace doticu_skylib { namespace Virtual {

    template <typename Type>
    Handle_t::Handle_t(Type* form_or_alias)
    {
        if (form_or_alias) {
            raw_handle = Handle_Policy_t::Self()->Handle(Type::kTypeID, form_or_alias);
        } else {
            raw_handle = Handle_Policy_t::Self()->Invalid_Handle();
        }
    }
    template <> Handle_t::Handle_t(void* form_or_alias) = delete;
    template <> Handle_t::Handle_t(Handle_t* form_or_alias) = delete;

}}
