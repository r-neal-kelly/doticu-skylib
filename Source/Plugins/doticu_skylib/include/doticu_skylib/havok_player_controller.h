/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_actor_controller.h"
#include "doticu_skylib/havok_player_base.h"
#include "doticu_skylib/havok_player_listener.h"

namespace doticu_skylib {

    class Havok_Player_Controller_t :   // bhkCharProxyController
        public Havok_Player_Listener_t, // 000
        public Havok_Actor_Controller_t // 010
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01EA0078, // 690816
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Havok_Player_Controller_t(); // 0

    public:
        Havok_Player_Base_t player_base;    // 340
        void*               unk_5A0;        // 5A0 (v_table: 0x017A47D0, size: 0x30, densely packed with same sized other types)
        u64                 unk_5A8;        // 5A8
    };
    STATIC_ASSERT(sizeof(Havok_Player_Controller_t) == 0x5B0);

}
