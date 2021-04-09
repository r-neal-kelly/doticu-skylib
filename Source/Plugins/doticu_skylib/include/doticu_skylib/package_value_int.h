/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value.h"

namespace doticu_skylib {

    class Package_Value_Int_t : // BGSPackageDataInt
        public Package_Value_t  // 00
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E231B8, // 685604
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Package_Value_Int_t(); // 0

    public:
        u64     pad_08; // 08
        Int_t   value;  // 10
        u32     pad_14; // 14

    public:
        Int_t   Int() const;
        void    Int(Int_t value);

    public:
        operator    Int_t() const;

    public:
        Package_Value_Int_t&    operator =(Int_t value);

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Package_Value_Int_t) == 0x18);

}
