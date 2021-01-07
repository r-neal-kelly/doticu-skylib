/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_static_flags.h"

#include "doticu_skylib/component_model_alternates.h"

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/script_type.h"

namespace doticu_skylib {

    class Static_t :
        public Bound_Object_t,      // 00
        public Model_Alternates_c   // 30
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::STATIC,
        };

    public:
        virtual ~Static_t(); // 0

    public:
        Float_t         unk_68; // 68
        u32             pad_6C; // 6C
        void*           unk_70; // 70
        Static_Flags_e  flags;  // 78
        u32             pad_7C; // 7C
    };
    STATIC_ASSERT(sizeof(Static_t) == 0x80);

}
