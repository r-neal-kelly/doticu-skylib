/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Count_x : public Data_x // ExtraCount
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::COUNT,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152BFE0,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Count_x();

    public:
        s16 count;  // 10
        u16 pad_12; // 12
        u32 pad_14; // 14
    };
    STATIC_ASSERT(sizeof(Count_x) == 0x18);

}