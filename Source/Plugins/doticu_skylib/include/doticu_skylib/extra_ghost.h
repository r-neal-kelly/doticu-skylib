/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Extra_Ghost_t :   // ExtraGhost
        public Extra_Data_t // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::GHOST,
        };

        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152F2A0, // 229888
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Ghost_t*> Create(Bool_t is_ghost);
        static void                 Destroy(some<Extra_Ghost_t*> x_ghost);

    public:
        virtual ~Extra_Ghost_t(); // 0

    public:
        Bool_t  is_ghost;   // 10
        u8      pad_11;     // 11
        u16     pad_12;     // 12
        u32     pad_14;     // 14
    };
    STATIC_ASSERT(sizeof(Extra_Ghost_t) == 0x18);

}
