/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/dynamic_array.h"

#include "doticu_skylib/actor_handle.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Extra_Followers_t :   // ExtraFollower
        public Extra_Data_t     // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::FOLLOWERS,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152BE80, // 229526
            };
            using Enum_t::Enum_t;
        };

    public:
        class Instance_t // FollowerInfo
        {
        public:
            Actor_Handle_t  handle;     // 0
            Float_t         distance;   // 4
        };
        STATIC_ASSERT(sizeof(Instance_t) == 0x8);

    public:
        virtual ~Extra_Followers_t(); // 0

    public:
        Array_t<Instance_t> instances; // 10
    };
    STATIC_ASSERT(sizeof(Extra_Followers_t) == 0x28);

}
