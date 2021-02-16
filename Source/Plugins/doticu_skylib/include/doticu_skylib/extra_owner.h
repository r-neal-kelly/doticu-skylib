/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Form_t;

    class Extra_Owner_t :   // ExtraOwnership
        public Extra_Data_t // 00
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
        static some<Extra_Owner_t*> Create(maybe<Form_t*> owner);
        static void                 Destroy(some<Extra_Owner_t*> x_count);

    public:
        virtual ~Extra_Owner_t(); // 0

    public:
        maybe<Form_t*> owner; // 10
    };
    STATIC_ASSERT(sizeof(Extra_Owner_t) == 0x18);

}
