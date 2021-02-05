/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_player.h"

namespace doticu_skylib {

    class Havok_Player_Ex_t :   // ahkpCharacterProxy
        public Havok_Player_t   // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI    = 0x01EA1870, // 690928
                V_TABLE = 0x017B1ED0, // 290759
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Havok_Player_Ex_t(); // 00

    public:
        void*   unk_F0; // F0
        u64     unk_F8; // F8
    };
    STATIC_ASSERT(sizeof(Havok_Player_Ex_t) == 0x100);

}
