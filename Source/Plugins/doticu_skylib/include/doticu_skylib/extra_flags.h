/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_extra_flags.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Flags_x : public Data_x // ExtraFlags
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::FLAGS,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152CBC0,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Flags_x();

    public:
        Extra_Flags_e   flags;  // 10
        u32             pad_14; // 14
    };
    STATIC_ASSERT(sizeof(Flags_x) == 0x18);

}
