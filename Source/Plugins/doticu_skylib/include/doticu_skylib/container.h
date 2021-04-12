/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/animated_object.h"
#include "doticu_skylib/component_container.h"
#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_model_alternates.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_openable.h"
#include "doticu_skylib/component_weight.h"
#include "doticu_skylib/enum_container_flags.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Reference_t;

    class Container_t :             // TESObjectCONT
        public Animated_Object_t,   // 00
        public Container_c,         // 30
        public Name_c,              // 48
        public Model_Alternates_c,  // 58
        public Weight_c,            // 90
        public Destructible_c,      // A0
        public Openable_c           // B0
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::CONTAINER,
        };

        static constexpr const char* SCRIPT_NAME = "Container";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E192A8, // 685079
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Reference_t*> Create_Reference(some<Container_t*> container, maybe<Reference_t*> at);

    public:
        virtual ~Container_t(); // 0

    public:
        u8                  unk_B8;             // B8
        Container_Flags_e   container_flags;    // B9
        u16                 pad_BA;             // BA
        u32                 pad_BC;             // BC
        void*               open_sound;         // C0
        void*               close_sound;        // C8
    };
    STATIC_ASSERT(sizeof(Container_t) == 0xD0);

}
