/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Extra_Worn_Left_t :   // ExtraWornLeft
        public Extra_Data_t     // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::WORN_LEFT,
        };

        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152C020, // 229539
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Worn_Left_t*> Create();
        static void                     Destroy(some<Extra_Worn_Left_t*> x_worn_left);

    public:
        virtual ~Extra_Worn_Left_t(); // 0
    };
    STATIC_ASSERT(sizeof(Extra_Worn_Left_t) == 0x10);

}
