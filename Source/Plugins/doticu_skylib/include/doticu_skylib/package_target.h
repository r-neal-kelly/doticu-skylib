/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_package_target.h"

#include "doticu_skylib/alias_id.h"
#include "doticu_skylib/form_id.h"
#include "doticu_skylib/form_type.h"
#include "doticu_skylib/reference_handle.h"

namespace doticu_skylib {

    class Form_t;

    class Package_Target_t
    {
    public:
        union Target_u
        {
            Reference_Handle_t  specific;
            Form_ID_t           form_id;
            Form_Type_e         form_type;
            Form_t*             linked;
            Alias_ID_t          alias_id;
        };
        STATIC_ASSERT(sizeof(Target_u) == 0x08);

    public:
        Package_Target_e    type;               // 00
        u8                  pad_01;             // 01
        u16                 pad_02;             // 02
        Target_u            target;             // 08
        Int_t               count_or_distance;  // 10
        u32                 pad_14;             // 14
    };
    STATIC_ASSERT(sizeof(Package_Target_t) == 0x18);

}
