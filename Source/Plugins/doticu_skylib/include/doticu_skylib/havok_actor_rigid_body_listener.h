/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Havok_Actor_Rigid_Body_Listener_t // hkpCharacterRigidBodyListener
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01EA00E0, // 690818
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Havok_Actor_Rigid_Body_Listener_t(); // 0
    };
    STATIC_ASSERT(sizeof(Havok_Actor_Rigid_Body_Listener_t) == 0x8);

}
