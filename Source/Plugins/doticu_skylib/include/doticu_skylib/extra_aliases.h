/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"

#include "doticu_skylib/extra_data.h"
#include "doticu_skylib/read_write_lock.h"

namespace doticu_skylib {

    class Alias_Base_t;
    class Package_t;
    class Quest_t;

    class Aliases_x : public Data_x
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::ALIASES,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                V_TABLE = 0x0152C9A0,
            };
            using Enum_t::Enum_t;
        };

    public:
        class Instance_t
        {
        public:
            Quest_t*                quest;      // 00
            Alias_Base_t*           alias_base; // 08
            Array_t<Package_t*>*    packages;   // 10
        };

    public:
        virtual ~Aliases_x();

        Array_t<Instance_t*>    instances;  // 10
        Read_Write_Lock_t       lock;       // 28
    };
    STATIC_ASSERT(sizeof(Aliases_x) == 0x30);

}
