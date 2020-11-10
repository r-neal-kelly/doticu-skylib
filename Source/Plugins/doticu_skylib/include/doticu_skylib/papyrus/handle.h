/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/utils.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/papyrus.h"

namespace doticu_skylib { namespace Papyrus {

    class Handle_t {
    public:
        static Registry_t* Registry();
        static Policy_t* Policy();

        u64 handle = 0;

        Handle_t(void* instance, Form_Type_t form_type);
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
