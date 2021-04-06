/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_package_value_type.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Package_Value_t   // IPackageData
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E22C00, // 514008
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Package_Value_t(); // 0

    public:
        Package_Value_Type_e    Type() const;

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Package_Value_t) == 0x08);

}
