/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value.h"

namespace doticu_skylib {

    class Package_Int_Value_t : public Package_Value_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                V_TABLE = 0x016060A8, // 252946
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Package_Int_Value_t(); // 0

    public:
        u64     pad_08; // 08
        Int_t   value;  // 10
        u32     pad_14; // 14

    public:
        inline Package_Int_Value_t& operator=(Int_t value)
        {
            SKYLIB_ASSERT(Type() == Package_Value_e::INT);

            this->value = value;
            return *this;
        }

        inline operator Int_t() const
        {
            SKYLIB_ASSERT(Type() == Package_Value_e::INT);

            return value;
        }
    };
    STATIC_ASSERT(sizeof(Package_Int_Value_t) == 0x18);

}
