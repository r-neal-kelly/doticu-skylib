/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_soul_level.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Extra_Soul_Level_t :  // ExtraSoul
        public Extra_Data_t     // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::SOUL_LEVEL,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                //V_TABLE = 0x,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Extra_Soul_Level_t(); // 0

    public:
        Soul_Level_e    level;  // 10
        u8              pad_11; // 11
        u16             pad_12; // 12
        u32             pad_14; // 14
    };
    STATIC_ASSERT(sizeof(Extra_Soul_Level_t) == 0x18);

}
