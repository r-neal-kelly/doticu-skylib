/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_attack_state.h"
#include "doticu_skylib/enum_fly_state.h"
#include "doticu_skylib/enum_knock_state.h"
#include "doticu_skylib/enum_life_state.h"
#include "doticu_skylib/enum_sit_sleep_state.h"
#include "doticu_skylib/enum_weapon_state.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Actor_State_t // ActorState
    {
    public:
        class Bits_A_t
        {
        public:
            u32 is_moving_back      : 1;    // 0::0
            u32 is_moving_forward   : 1;    // 0::1
            u32 is_moving_right     : 1;    // 0::2
            u32 is_moving_left      : 1;    // 0::3

            u32 unk_0_4             : 2;    // 0::4 - 0::5

            u32 is_walking          : 1;    // 0::6
            u32 is_running          : 1;    // 0::7
            u32 is_sprinting        : 1;    // 1::0
            u32 is_sneaking         : 1;    // 1::1
            u32 is_swimming         : 1;    // 1::2

            u32 unk_1_3             : 3;    // 1::3 - 1::5

            u32 sit_sleep_state     : 4;    // 1::6 - 2::1
            u32 fly_state           : 3;    // 2::2 - 2::4
            u32 life_state          : 4;    // 2::5 - 3::0
            u32 knock_state         : 3;    // 3::1 - 3::3
            u32 attack_state        : 4;    // 3::4 - 3::7
        };
        STATIC_ASSERT(sizeof(Bits_A_t) == 0x4);

        class Bits_B_t
        {
        public:
            u32 is_talking_to_player    : 1;    // 4::0 (doesn't seem to be accurate)
            u32 is_forced_to_run        : 1;    // 4::1
            u32 is_forced_to_sneak      : 1;    // 4::2
            u32 is_head_tracking        : 1;    // 4::3
            u32 is_reanimating          : 1;    // 4::4

            u32 weapon_state            : 3;    // 4::5 - 4::7

            u32 wants_to_block          : 1;    // 5::0
            u32 is_flight_blocked       : 1;    // 5::1

            u32 recoil_state            : 2;    // 5::2 - 5::3 (or is this a value?)

            u32 is_allowed_to_fly       : 1;    // 5::4
            u32 is_staggered            : 1;    // 5::5
        };
        STATIC_ASSERT(sizeof(Bits_B_t) == 0x4);

    public:
        virtual ~Actor_State_t(); // 0

    public:
        Bits_A_t    bits_a; // 08
        Bits_B_t    bits_b; // 0C

    public:
        Attack_State_e      Attack_State();
        Fly_State_e         Fly_State();
        Knock_State_e       Knock_State();
        Life_State_e        Life_State();
        Sit_Sleep_State_e   Sit_Sleep_State();
        Weapon_State_e      Weapon_State();

        Bool_t              Is_Moving();
        Bool_t              Is_Sneaking();
        Bool_t              Is_Forced_To_Sneak();

        Bool_t              Has_Weapon_Drawn();
        Bool_t              Has_Weapon_Sheathed();
    };
    STATIC_ASSERT(sizeof(Actor_State_t) == 0x10);

}
