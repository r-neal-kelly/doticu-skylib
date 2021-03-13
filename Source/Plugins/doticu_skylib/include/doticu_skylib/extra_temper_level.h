/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"
#include "doticu_skylib/temper_level.h"

namespace doticu_skylib {

    class Extra_Temper_Level_t :    // ExtraHealth
        public Extra_Data_t         // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::TEMPER_LEVEL,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                V_TABLE = 0x0152C060, // 229541
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Temper_Level_t*>  Create();
        static some<Extra_Temper_Level_t*>  Create(Temper_Level_t temper_level);
        static some<Extra_Temper_Level_t*>  Create(const Extra_Temper_Level_t& other);
        static void                         Destroy(some<Extra_Temper_Level_t*> x_temper_level);

    public:
        virtual ~Extra_Temper_Level_t(); // 0

    public:
        Temper_Level_t  temper_level;   // 10
        u32             pad_14;         // 14

    public:
        Temper_Level_t  Temper_Level() const;
        void            Temper_Level(Temper_Level_t temper_level);

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Extra_Temper_Level_t) == 0x18);

}
