/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value.h"

namespace doticu_skylib {

    class Package_Value_Float_t :   // BGSPackageDataFloat
        public Package_Value_t      // 00
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E230F0, // 685602
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Package_Value_Float_t(); // 0

    public:
        u64     pad_08; // 08
        Float_t value;  // 10
        u32     pad_14; // 14

    public:
        Float_t Float() const;
        void    Float(Float_t value);

    public:
        operator    Float_t() const;

    public:
        Package_Value_Float_t&  operator =(Float_t value);

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Package_Value_Float_t) == 0x18);

}
