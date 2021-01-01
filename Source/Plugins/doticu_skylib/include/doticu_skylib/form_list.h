/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

#include "doticu_skylib/collections.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/script_type.h"

namespace doticu_skylib {

    class Form_List_t : public Form_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::FORM_LIST,
        };

    public:
        virtual ~Form_List_t(); // 0

        Array_t<Form_t*>    forms;                  // 20
        Array_t<Form_ID_t>* added_form_ids;         // 38
        u32                 added_form_id_count;    // 40
        u32                 pad_44;                 // 44

    public:
        Bool_t Has(some<Form_t*> form);
        size_t Count();
    };
    STATIC_ASSERT(sizeof(Form_List_t) == 0x48);

}
