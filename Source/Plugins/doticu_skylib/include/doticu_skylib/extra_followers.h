/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"

#include "doticu_skylib/reference_handle.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Follower_Info_t
    {
    public:
        Reference_Handle_t  handle;     // 0
        Float_t             distance;   // 4
    };
    STATIC_ASSERT(sizeof(Follower_Info_t) == 0x8);

    class Followers_x : public Data_x // ExtraFollower
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
                //V_TABLE = 0x, (find on player when someone is following them)
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Followers_x();

    public:
        Array_t<Follower_Info_t> follower_infos; // 10
    };
    STATIC_ASSERT(sizeof(Followers_x) == 0x28);

}
