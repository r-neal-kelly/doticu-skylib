/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Extra_Cannot_Wear_t : // ExtraCannotWear
        public Extra_Data_t     // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::CANNOT_WEAR,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                V_TABLE = 0x0152C040, // 229540
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Cannot_Wear_t*>   Create();
        static some<Extra_Cannot_Wear_t*>   Create(const Extra_Cannot_Wear_t& other);
        static void                         Destroy(some<Extra_Cannot_Wear_t*> x_cannot_wear);

    public:
        virtual ~Extra_Cannot_Wear_t(); // 0

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Extra_Cannot_Wear_t) == 0x10);

}
