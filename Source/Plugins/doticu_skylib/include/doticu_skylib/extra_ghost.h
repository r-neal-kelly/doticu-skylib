/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Ghost_x : public Data_x // ExtraGhost
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::GHOST,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152F2A0,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Ghost_x();

    public:
        Bool_t  is_ghost;   // 10
        u8      pad_11;     // 11
        u16     pad_12;     // 12
        u32     pad_14;     // 14
    };
    STATIC_ASSERT(sizeof(Ghost_x) == 0x18);

}
