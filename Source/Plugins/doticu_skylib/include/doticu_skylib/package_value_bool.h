/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value.h"

namespace doticu_skylib {

    class Package_Value_Bool_t :    // BGSPackageDataBool
        public Package_Value_t      // 00
    {
    public:
        enum
        {
            IS_FALSE    = 0,
            IS_TRUE     = 2,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E22C28, // 514009
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Package_Value_Bool_t(); // 0

    public:
        u32 value;  // 08
        u32 pad_0C; // 0C

    public:
        Bool_t  Bool() const;
        void    Bool(Bool_t value);

    public:
        operator    Bool_t() const;

    public:
        Bool_t                  operator !() const;
        Package_Value_Bool_t&   operator =(Bool_t value);

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Package_Value_Bool_t) == 0x10);

}
