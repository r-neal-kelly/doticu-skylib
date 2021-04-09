/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ai_target_handle.h"
#include "doticu_skylib/package_value.h"

namespace doticu_skylib {

    class Package_Value_List_t :    // BGSPackageDataObjectList
        public AI_Target_Handle_t,  // 00
        public Package_Value_t      // 08
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E23ED0, // 514018
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Package_Value_List_t(); // 0

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Package_Value_List_t) == 0x10);

}
