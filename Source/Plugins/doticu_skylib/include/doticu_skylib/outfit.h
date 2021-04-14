/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Bound_Object_t;
    class Reference_t;

    class Outfit_t :    // BGSOutfit
        public Form_t   // 00
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::OUTFIT,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E18348, // 513971
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Outfit_t(); // 0

    public:
        Array_t<maybe<Bound_Object_t*>> entries;    // 20

    public:
        void    Add_Items_To(some<Reference_t*> reference);
    };
    STATIC_ASSERT(sizeof(Outfit_t) == 0x38);

}
