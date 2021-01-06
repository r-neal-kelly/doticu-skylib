/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value.h"

namespace doticu_skylib {

    class Package_Location_t;

    class Package_Location_Value_t : public Package_Value_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                V_TABLE = 0x01606520, // 252956
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Package_Location_Value_t(); // 0

    public:
        u64                 pad_08; // 08
        Package_Location_t* value;  // 10
        void*               unk_18; // 18

    public:
        inline Package_Location_Value_t& operator=(Package_Location_t* value)
        {
            SKYLIB_ASSERT(Type() == Package_Value_e::LOCATION);

            this->value = value;
            return *this;
        }

        inline operator Package_Location_t* () const
        {
            SKYLIB_ASSERT(Type() == Package_Value_e::LOCATION);

            return value;
        }
    };
    STATIC_ASSERT(sizeof(Package_Location_Value_t) == 0x20);

}
