/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ai_target_handle.h"
#include "doticu_skylib/package_value.h"

namespace doticu_skylib {

    class Package_Target_t;

    class Package_Value_Reference_t :   // BGSPackageDataRef
        public AI_Target_Handle_t,      // 00
        public Package_Value_t          // 08
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E24158, // 685636
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Package_Value_Reference_t(); // 0

    public:
        u64                         pad_08; // 08
        maybe<Package_Target_t*>    value;  // 10 (PTDA)

    public:
        maybe<Package_Target_t*>    Target() const;
        void                        Target(maybe<Package_Target_t*> value);

    public:
        operator    maybe<Package_Target_t*>() const;

    public:
        Package_Value_Reference_t&  operator =(maybe<Package_Target_t*> value);

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Package_Value_Reference_t) == 0x20);

}
