/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Actor_State_t
    {
    public:
        class Weapon_e : Enum_t<u8>
        {
            enum : u8
            {
                SHEATHED            = 0,
                WANTS_TO_DRAW       = 1,
                DRAWING             = 2,
                DRAWN               = 3,
                WANTS_TO_SHEATHE    = 4,
                SHEATHING           = 5,
            };
            using Enum_t::Enum_t;
        };

        class State_t
        {
        public:
            Bool_t moving_back : 1;         // 0::0
            Bool_t moving_forward : 1;      // 0::1
            Bool_t moving_right : 1;        // 0::2
            Bool_t moving_left : 1;         // 0::3
            Bool_t unk_0_4 : 1;             // 0::4
            Bool_t unk_0_5 : 1;             // 0::5
            Bool_t walking : 1;             // 0::6
            Bool_t running : 1;             // 0::7
            Bool_t sprinting : 1;           // 1::0
            Bool_t sneaking : 1;            // 1::1
            Bool_t swimming : 1;            // 1::2
            Bool_t unk_1_3 : 1;             // 1::3
            Bool_t unk_1_4 : 1;             // 1::4
            Bool_t unk_1_5 : 1;             // 1::5
            Bool_t sitting_sleeping_0 : 1;  // 1::6
            Bool_t sitting_sleeping_1 : 1;  // 1::7
            Bool_t sitting_sleeping_2 : 1;  // 2::0
            Bool_t sitting_sleeping_3 : 1;  // 2::1
            Bool_t flying_0 : 1;            // 2::2
            Bool_t flying_1 : 1;            // 2::3
            Bool_t flying_2 : 1;            // 2::4
            Bool_t living_0 : 1;            // 2::5
            Bool_t living_1 : 1;            // 2::6
            Bool_t living_2 : 1;            // 2::7
            Bool_t living_3 : 1;            // 3::0
            Bool_t knocked_0 : 1;           // 3::1
            Bool_t knocked_1 : 1;           // 3::2
            Bool_t knocked_2 : 1;           // 3::3
            Bool_t melee_0 : 1;             // 3::4
            Bool_t melee_1 : 1;             // 3::5
            Bool_t melee_2 : 1;             // 3::6
            Bool_t melee_3 : 1;             // 3::7
            Bool_t talking_to_player : 1;   // 4::0
            Bool_t force_running : 1;       // 4::1
            Bool_t force_sneaking : 1;      // 4::2
            Bool_t head_tracking : 1;       // 4::3
            Bool_t reanimating : 1;         // 4::4
            Bool_t weapon_0 : 1;            // 4::5
            Bool_t weapon_1 : 1;            // 4::6
            Bool_t weapon_2 : 1;            // 4::7
            Bool_t wants_blocking : 1;      // 5::0
            Bool_t flight_blocked : 1;      // 5::1
            Bool_t recoil_0 : 1;            // 5::2
            Bool_t recoil_1 : 1;            // 5::3
            Bool_t flying_allowed : 1;      // 5::4
            Bool_t staggered : 1;           // 5::5
        };

    public:
        virtual ~Actor_State_t();

        State_t state;

        Bool_t Is_Moving();
        Weapon_e Weapon_State();
    };
    STATIC_ASSERT(sizeof(Actor_State_t) == 0x10);

}
