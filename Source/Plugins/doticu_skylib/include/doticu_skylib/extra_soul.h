/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_soul_level.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Soul_x : public Data_x // ExtraSoul
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::SOUL,
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
        virtual ~Soul_x();

    public:
        Soul_Level_e    soul_level; // 10
        u8              pad_11;     // 11
        u16             pad_12;     // 12
        u32             pad_14;     // 14
    };
    STATIC_ASSERT(sizeof(Soul_x) == 0x18);

}
