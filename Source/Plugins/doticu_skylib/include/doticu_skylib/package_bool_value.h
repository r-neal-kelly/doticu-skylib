/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value.h"

namespace doticu_skylib {

    class Package_Bool_Value_t : public Package_Value_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                V_TABLE = 0x01605DE0, // 252944
            };
            using Enum_t::Enum_t;
        };

        enum
        {
            IS_FALSE    = 0,
            IS_TRUE     = 2,
        };

    public:
        virtual ~Package_Bool_Value_t(); // 0

    public:
        u32 value;  // 8
        u32 pad_0C; // C

    public:
        inline Package_Bool_Value_t& operator=(Bool_t value)
        {
            SKYLIB_ASSERT(Type() == Package_Value_e::BOOL);

            if (value) {
                this->value = IS_TRUE;
            } else {
                this->value = IS_FALSE;
            }
            return *this;
        }

        inline operator Bool_t() const
        {
            SKYLIB_ASSERT(Type() == Package_Value_e::BOOL);

            return value > 0;
        }
    };
    STATIC_ASSERT(sizeof(Package_Bool_Value_t) == 0x10);

}
