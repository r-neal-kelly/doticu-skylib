/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_soul_level.h"
#include "doticu_skylib/misc.h"

namespace doticu_skylib {

    class Soul_Gem_t :  // TESSoulGem
        public Misc_t   // 000
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::SOUL_GEM,
        };

        static constexpr const char* SCRIPT_NAME = "SoulGem";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E19738, // 513979
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Soul_Gem_t(); // 00

    public:
        maybe<Soul_Gem_t*>  filled_soul_gem;    // 100 (NAM0)
        Soul_Level_e        default_soul_level; // 108
        Soul_Level_e        maximum_soul_level; // 109
        u16                 unk_10A;            // 10A
        u32                 unk_10C;            // 10C
    };
    STATIC_ASSERT(sizeof(Soul_Gem_t) == 0x110);

}
