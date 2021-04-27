/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Form_List_t : // BGSListForm
        public Form_t   // 00
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::FORM_LIST,
        };

        static constexpr const char* SCRIPT_NAME = "FormList";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                ADD_FORM            = 0x002C53D0, // 20470
                REMOVE_ADDED_FORM   = 0x002C5570, // 20471
                REVERT              = 0x002C5300, // 20469
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Form_List_t(); // 0

    public:
        Array_t<maybe<Form_t*>>     static_forms;           // 20
        maybe<Array_t<Form_ID_t>*>  dynamic_form_ids;       // 38
        u32                         dynamic_form_id_count;  // 40
        u32                         pad_44;                 // 44

    public:
        Bool_t          Has(some<Form_t*> form);
        size_t          Count();

        void            Add_Form(some<Form_t*> form);
        void            Remove_Added_Form(some<Form_t*> form);
        void            Revert();

        maybe<Form_t*>  At(size_t index);
        maybe<Form_t*>& Static_At(size_t index);
        Form_ID_t&      Dynamic_At(size_t index);

    public:
        maybe<Form_t*>& operator [](size_t index);
        maybe<Form_t*>  operator ()(size_t index);

    public:
        void    Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Form_List_t) == 0x48);

}
