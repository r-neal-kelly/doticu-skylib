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

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                V_TABLE = 0x0152F2E0, // 229890
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Soul_Level_t*>    Create();
        static some<Extra_Soul_Level_t*>    Create(Soul_Level_e soul_level);
        static some<Extra_Soul_Level_t*>    Create(const Extra_Soul_Level_t& other);
        static void                         Destroy(some<Extra_Soul_Level_t*> x_soul_level);

    public:
        virtual ~Extra_Soul_Level_t(); // 0

    public:
        Soul_Level_e    soul_level; // 10
        u8              pad_11;     // 11
        u16             pad_12;     // 12
        u32             pad_14;     // 14

    public:
        Soul_Level_e    Soul_Level();
        void            Soul_Level(Soul_Level_e soul_level);

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Extra_Soul_Level_t) == 0x18);

}
