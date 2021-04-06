/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value.h"

namespace doticu_skylib {

    class Package_Value_List_t :    // BGSPackageDataObjectList
        public Package_Value_t      // 00
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI    = 0x01E23ED0, // 514018
                V_TABLE = 0x01606EE0, // 253007
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Package_Value_List_t(); // 0

    public:
        u64     pad_08; // 08
        u64     value;  // 10
        void*   unk_18; // 18

    public:
        //maybe<Package_Target_t*>    Value() const;
        //void                        Value(maybe<Package_Target_t*> value);

    public:
        //operator    maybe<Package_Target_t*>() const;

    public:
        //Package_Value_Target_t& operator =(maybe<Package_Target_t*> value);

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Package_Value_List_t) == 0x20);

}
