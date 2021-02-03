/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_saveable_base.h"

namespace doticu_skylib {

    class Havok_Player_t;
    class Havok_Player_Ex_t;

    class Havok_Player_Base_t :         // bhkCharacterProxy
        public Havok_Saveable_Base_t    // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01EA0050, // 690815
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Havok_Player_Base_t(); // 00

    public:
        Byte_t data_20[0x240]; // 20

    public:
        maybe<Havok_Player_t*>      Player();
        maybe<Havok_Player_Ex_t*>   Player_Ex();
    };
    STATIC_ASSERT(sizeof(Havok_Player_Base_t) == 0x260);

}
