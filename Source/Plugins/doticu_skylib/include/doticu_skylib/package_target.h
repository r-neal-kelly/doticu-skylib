/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/alias_id.h"
#include "doticu_skylib/enum_form_type.h"
#include "doticu_skylib/enum_package_target_type.h"
#include "doticu_skylib/form_id.h"
#include "doticu_skylib/reference_handle.h"

namespace doticu_skylib {

    class Form_t;
    class Object_t;
    class Reference_t;

    class Package_Target_t  // PackageTarget
    {
    public:
        union Target_u
        {
        public:
            Alias_ID_t          alias_id;
            maybe<Form_Type_e>  form_type;
            maybe<Form_t*>      linked_form;
            maybe<Object_t*>    object;
            Reference_Handle_t  reference_handle;

        public:
            Target_u();
            ~Target_u();
        };
        STATIC_ASSERT(sizeof(Target_u) == 0x08);

    public:
        Package_Target_Type_e   target_type;        // 00
        u8                      pad_01;             // 01
        u16                     pad_02;             // 02
        Target_u                target;             // 08
        Int_t                   count_or_distance;  // 10
        u32                     pad_14;             // 14

    public:
        Alias_ID_t          Alias_ID() const;
        void                Alias_ID(Alias_ID_t alias_id);

        maybe<Form_Type_e>  Form_Type() const;
        void                Form_Type(maybe<Form_Type_e> form_type);

        maybe<Form_t*>      Linked_Form() const;
        void                Linked_Form(maybe<Form_t*> linked_form);

        maybe<Object_t*>    Object() const;
        void                Object(maybe<Object_t*> object);

        maybe<Reference_t*> Reference() const;
        void                Reference(maybe<Reference_t*> reference);

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Package_Target_t) == 0x18);

}
