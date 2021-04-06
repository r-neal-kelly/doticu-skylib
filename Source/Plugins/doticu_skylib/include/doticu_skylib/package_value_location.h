/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value.h"

namespace doticu_skylib {

    class Package_Location_t;

    class Package_Value_Location_t :    // BGSPackageDataLocation (BGSPackageDataLocationWrapper?)
        public Package_Value_t          // 00
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI    = 0x01E232A8, // 685607
                V_TABLE = 0x01606520, // 252956
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Package_Value_Location_t(); // 0

    public:
        u64                         pad_08; // 08
        maybe<Package_Location_t*>  value;  // 10
        void*                       unk_18; // 18

    public:
        maybe<Package_Location_t*>  Value() const;
        void                        Value(maybe<Package_Location_t*> value);

    public:
        operator    maybe<Package_Location_t*>() const;

    public:
        Package_Value_Location_t&   operator =(maybe<Package_Location_t*> value);

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Package_Value_Location_t) == 0x20);

}
