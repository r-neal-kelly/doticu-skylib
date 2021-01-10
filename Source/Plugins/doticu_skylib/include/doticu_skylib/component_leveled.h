/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Form_t;
    class Global_t;
    class Leveled_Entry_t;

    class Leveled_c : public Form_Data_c // TESLeveledList
    {
    public:
        virtual ~Leveled_c(); // 0

        Leveled_Entry_t*    leveled_entries;        // 08 (LVLO Leveled Object) (see SimpleArray)
        u8                  chance_of_none;         // 10
        u8                  leveled_flags;          // 11
        u8                  leveled_entry_count;    // 12
        u8                  unk_13;                 // 13
        u32                 pad_14;                 // 14
        void*               unk_18;                 // 18
        Global_t*           chance_of_none_global;  // 20
    };
    STATIC_ASSERT(sizeof(Leveled_c) == 0x28);

}
