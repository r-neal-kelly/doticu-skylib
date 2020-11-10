/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/virtual.h"

namespace doticu_skylib { namespace Virtual {

    class Machine_t;
    class Handle_Policy_t;

    class Handle_t {
    public:
        static Registry_t* Registry();
        static Machine_t* Machine();
        static Handle_Policy_t* Policy();

        u64 handle = 0;

        Handle_t(void* form, Form_Type_t form_type);
        template <typename Type_t>
        Handle_t(Type_t* instance);
        Handle_t(Form_t* form);
        Handle_t();

        Bool_t Is_Valid();
        Bool_t Has_Form_Type(Form_Type_t form_type);

        operator u64();
    };
    STATIC_ASSERT(sizeof(Handle_t) == 0x8);

}}
