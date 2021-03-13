/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Potion_t;

    class Extra_Poison_t :  // ExtraPoison
        public Extra_Data_t // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::POISON,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                V_TABLE = 0x0152C460, // 229573
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Poison_t*>    Create();
        static some<Extra_Poison_t*>    Create(maybe<Potion_t*> poison, u32 count);
        static some<Extra_Poison_t*>    Create(const Extra_Poison_t& other);
        static void                     Destroy(some<Extra_Poison_t*> x_poison);

    public:
        virtual ~Extra_Poison_t(); // 0

    public:
        maybe<Potion_t*>    poison; // 10
        u32                 count;  // 18
        u32                 pad_1C; // 1C

    public:
        maybe<Potion_t*>    Poison();
        void                Poison(maybe<Potion_t*> poison);

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Extra_Poison_t) == 0x20);

}
