/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value.h"

namespace doticu_skylib {

    class Package_Float_Value_t : public Package_Value_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                V_TABLE = 0x01605F40, // 252945
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Package_Float_Value_t(); // 0

    public:
        u64     pad_08; // 08
        Float_t value;  // 10
        u32     pad_14; // 14

    public:
        inline Package_Float_Value_t& operator=(Float_t value)
        {
            SKYLIB_ASSERT(Type() == Package_Value_e::FLOAT);

            this->value = value;
            return *this;
        }

        inline operator Float_t() const
        {
            SKYLIB_ASSERT(Type() == Package_Value_e::FLOAT);

            return value;
        }
    };
    STATIC_ASSERT(sizeof(Package_Float_Value_t) == 0x18);

}
