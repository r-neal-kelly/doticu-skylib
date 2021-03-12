/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/component_model_alternates.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/enum_static_flags.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Reference_t;

    class Static_t :                // TESObjectSTAT
        public Bound_Object_t,      // 00
        public Model_Alternates_c   // 30
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::STATIC,
        };

        static constexpr const char* SCRIPT_NAME = "Static";

    public:
        static some<Static_t*>      X_Marker();
        static some<Static_t*>      X_Marker_Heading();

        static some<Reference_t*>   Create_X_Marker(maybe<Reference_t*> at);
        static some<Reference_t*>   Create_X_Marker_Heading(maybe<Reference_t*> at);

    public:
        virtual ~Static_t(); // 0

    public:
        Float_t         unk_68;         // 68
        u32             pad_6C;         // 6C
        void*           unk_70;         // 70
        Static_Flags_e  static_flags;   // 78
        u32             pad_7C;         // 7C
    };
    STATIC_ASSERT(sizeof(Static_t) == 0x80);

}
