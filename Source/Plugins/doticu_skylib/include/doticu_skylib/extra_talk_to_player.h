/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Extra_Talk_To_Player_t :  // ExtraCanTalkToPlayer
        public Extra_Data_t         // 00
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
                V_TABLE = 0x0152C740, // 229596
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Talk_To_Player_t*>    Create(Bool_t can_talk_to_player);
        static void                             Destroy(some<Extra_Talk_To_Player_t*> x_talk_to_player);

    public:
        virtual ~Extra_Talk_To_Player_t(); // 0

    public:
        Bool_t  can_talk_to_player; // 10
        u8      pad_11;             // 11
        u16     pad_12;             // 12
        u32     pad_14;             // 14
    };
    STATIC_ASSERT(sizeof(Extra_Talk_To_Player_t) == 0x18);

}
