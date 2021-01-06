/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value.h"

namespace doticu_skylib {

    class Topic_t;

    class Package_Topic_Value_t : public Package_Value_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                V_TABLE = 0x016073F8, // 253033
            };
            using Enum_t::Enum_t;
        };

        union Value_u
        {
            Topic_t*    topic;
            u32         sub_type;
        };
        STATIC_ASSERT(sizeof(Value_u) == 0x8);

    public:
        virtual ~Package_Topic_Value_t(); // 0

    public:
        u64     pad_08;         // 08
        Bool_t  is_sub_type;    // 10
        u8      pad_11;         // 11
        u16     pad_12;         // 12
        u32     pad_14;         // 14
        Value_u value;          // 18

    public:
        inline Package_Topic_Value_t& operator=(Topic_t* value)
        {
            SKYLIB_ASSERT(Type() == Package_Value_e::TOPIC);

            is_sub_type = false;
            this->value.topic = value;
            return *this;
        }

        inline Package_Topic_Value_t& operator=(u32 sub_type)
        {
            SKYLIB_ASSERT(Type() == Package_Value_e::TOPIC);

            is_sub_type = true;
            this->value.sub_type = sub_type;
            return *this;
        }

        inline operator Topic_t* () const
        {
            SKYLIB_ASSERT(Type() == Package_Value_e::TOPIC);

            if (!is_sub_type) {
                return value.topic;
            } else {
                nullptr;
            }
        }

        inline operator u32 () const
        {
            SKYLIB_ASSERT(Type() == Package_Value_e::TOPIC);

            if (is_sub_type) {
                return value.sub_type;
            } else {
                return 0;
            }
        }
    };
    STATIC_ASSERT(sizeof(Package_Topic_Value_t) == 0x20);

}
