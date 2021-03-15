/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Extra_Count_t :   // ExtraCount
        public Extra_Data_t // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::COUNT,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                V_TABLE = 0x0152BFE0, // 229537
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Count_t*> Create();
        static some<Extra_Count_t*> Create(s16 count);
        static some<Extra_Count_t*> Create(const Extra_Count_t& other);
        static void                 Destroy(some<Extra_Count_t*> x_count);

    public:
        virtual ~Extra_Count_t(); // 0

    public:
        s16 count;  // 10 (do we know this is a s16 because of barter gold limits?)
        u16 pad_12; // 12
        u32 pad_14; // 14

    public:
        s16     Count();
        void    Count(s16 count);
        s16     Increment_Count(s16 amount);
        s16     Decrement_Count(s16 amount);

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Extra_Count_t) == 0x18);

}
