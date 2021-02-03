/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Havok_Player_Listener_t // hkpCharacterProxyListener
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E9FFF0, // 690813
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Havok_Player_Listener_t(); // 0
    };
    STATIC_ASSERT(sizeof(Havok_Player_Listener_t) == 0x8);

}
