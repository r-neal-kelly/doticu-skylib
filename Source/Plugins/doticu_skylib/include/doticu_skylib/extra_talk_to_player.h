/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Talk_To_Player_x : public Data_x // ExtraCanTalkToPlayer
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::TALK_TO_PLAYER,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152C740,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Talk_To_Player_x();

    public:
        Bool_t  can_talk;   // 10
        u8      pad_11;     // 11
        u16     pad_12;     // 12
        u32     pad_14;     // 14
    };
    STATIC_ASSERT(sizeof(Talk_To_Player_x) == 0x18);

}
