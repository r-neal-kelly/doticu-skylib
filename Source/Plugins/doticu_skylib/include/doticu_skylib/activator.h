/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_activator_flags.h"

#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_model_alternates.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_openable.h"

#include "doticu_skylib/animated_object.h"
#include "doticu_skylib/unknown.h"

namespace doticu_skylib {

    class Activator_t :
        public Animated_Object_t,   // 00
        public Name_c,              // 30
        public Model_Alternates_c,  // 40
        public Destructible_c,      // 78
        public Openable_c,          // 88
        public Keywords_c           // 90
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ACTIVATOR,
        };

    public:
        virtual ~Activator_t(); // 0

    public:
        void*               unk_A8;             // A8
        void*               unk_B0;             // B0
        void*               unk_B8;             // B8
        Activator_Flags_e   activator_flags;    // C0
        u16                 pad_C2;             // C2
        u32                 pad_C4;             // C4
    };
    STATIC_ASSERT(sizeof(Activator_t) == 0xC8);

}
