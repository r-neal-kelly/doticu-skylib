/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "doticu_skylib/havok_saveable_base.h"

namespace doticu_skylib {

    class Havok_Rigid_Body_Base_t;

    class Havok_Actor_Rigid_Body_Base_t :   // bhkCharacterRigidBody
        public Havok_Saveable_Base_t        // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI    = 0x01EA0150, // 690820
                V_TABLE = 0x017A5410, // 289858
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Havok_Actor_Rigid_Body_Base_t();

    public:
        maybe<Havok_Rigid_Body_Base_t*> rigid_body_base;    // 20
        u64                             unk_28;             // 28 (can be a pointer?)
    };
    STATIC_ASSERT(sizeof(Havok_Actor_Rigid_Body_Base_t) == 0x30);

}
