/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_leveled.h"

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Leveled_Item_t :      // TESLevItem
        public Bound_Object_t,  // 00
        public Leveled_c        // 30
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::LEVELED_ITEM,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E15668, // 513952
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Leveled_Item_t(); // 0
    };
    STATIC_ASSERT(sizeof(Leveled_Item_t) == 0x58);

}
