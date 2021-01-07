/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Form_t;
    class Global_t;

    class Leveled_c : public Form_Data_c // TESLeveledList
    {
    public:
        class Entry_t
        {
        public:
            Form_t* form;   // 00
            u16     count;  // 08
            u16     level;  // 0A
            u32     pad_0C; // 0C
            void*   extra;  // 10
        };

    public:
        virtual ~Leveled_c(); // 0

        Entry_t*    leveled_entries;        // 08
        u8          chance_of_none;         // 10
        u8          leveled_flags;          // 11
        u8          leveled_entry_count;    // 12
        u8          unk_13;                 // 13
        u32         pad_14;                 // 14
        void*       unk_18;                 // 18
        Global_t*   chance_of_none_global;  // 20;
    };
    STATIC_ASSERT(sizeof(Leveled_c) == 0x28);

}
