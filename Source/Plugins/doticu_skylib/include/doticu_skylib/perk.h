/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/dynamic_array.h"

#include "doticu_skylib/component_description.h"
#include "doticu_skylib/component_icon.h"
#include "doticu_skylib/component_name.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Perk_t :              // BGSPerk
        public Form_t,          // 00
        public Name_c,          // 20
        public Description_c,   // 30
        public Icon_c           // 40
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::PERK,
        };

    public:
        virtual ~Perk_t(); // 0

    public:
        Bool_t          has_trait;      // 50 (unused)
        s8              level;          // 51
        s8              rank_count;     // 52
        Bool_t          is_playable;    // 53
        Bool_t          is_hidden;      // 54
        u8              pad_55;         // 55
        u16             pad_56;         // 56
        void*           conditions;     // 58
        Array_t<void*>  perk_entries;   // 60
        Perk_t*         next_perk;      // 78
    };
    STATIC_ASSERT(sizeof(Perk_t) == 0x80);

}
