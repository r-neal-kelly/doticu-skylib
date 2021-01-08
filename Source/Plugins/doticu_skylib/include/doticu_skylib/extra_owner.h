/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Form_t;

    class Owner_x : public Data_x // ExtraOwnership
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::OWNER,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152BF80,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Owner_x();

    public:
        Form_t* owner; // 10
    };
    STATIC_ASSERT(sizeof(Owner_x) == 0x18);

}
