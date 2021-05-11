/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Game_Timer_t  // BSTimer
    {
    public:
        u64     unk_00;                 // 00
        u32     last_performance_count; // 08
        Float_t clamp;                  // 10
        Float_t clamp_remainder;        // 14
        Float_t delta;                  // 18
        Float_t real_time_delta;        // 1C
        u32     unk_20;                 // 20
        u32     total_time;             // 24 (I think.)
        Float_t unk_28;                 // 28
        u32     unk_2C;                 // 2C
        u32     unk_30;                 // 30
        u32     unk_34;                 // 34
        u8      unk_38;                 // 38
        u8      unk_39;                 // 39
        Bool_t  unk_3A;                 // 3A
        u8      pad_3B;                 // 3B
        u32     pad_3C;                 // 3C

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Game_Timer_t) == 0x40);

}
