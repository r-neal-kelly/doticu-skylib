/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value.h"

namespace doticu_skylib {

    class Package_Target_t;

    class Package_Reference_Value_t : public Package_Value_t // Package_Single_Reference_Value_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                V_TABLE = 0x016072A0, // 253026
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Package_Reference_Value_t(); // 0

    public:
        u64                 pad_08; // 08
        Package_Target_t*   value;  // 10
        void*               unk_18; // 18

    public:
        inline Package_Reference_Value_t& operator=(Package_Target_t* value)
        {
            SKYLIB_ASSERT(Type() == Package_Value_e::REFERENCE);

            this->value = value;
            return *this;
        }

        inline operator Package_Target_t* () const
        {
            SKYLIB_ASSERT(Type() == Package_Value_e::REFERENCE);

            return value;
        }
    };
    STATIC_ASSERT(sizeof(Package_Reference_Value_t) == 0x20);

}
