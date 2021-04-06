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

    class Package_Target_t  // PackageTarget
    {
    public:
        union Target_u
        {
        public:
            Reference_Handle_t  specific;
            Form_ID_t           form_id;
            Form_Type_e         form_type;
            maybe<Form_t*>      linked;
            Alias_ID_t          alias_id;

        public:
            Target_u() :
                linked(none<Form_t*>())
            {
            }

            ~Target_u()
            {
                this->linked = none<Form_t*>();
            }
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
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Package_Target_t) == 0x18);

}
