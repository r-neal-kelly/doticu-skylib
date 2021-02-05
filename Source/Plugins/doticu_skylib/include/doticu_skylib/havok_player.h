/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "doticu_skylib/havok_array.h"
#include "doticu_skylib/havok_collision.h"
#include "doticu_skylib/havok_entity_listener.h"
#include "doticu_skylib/havok_phantom_listener.h"
#include "doticu_skylib/havok_quad.h"
#include "doticu_skylib/havok_reference.h"

namespace doticu_skylib {

    class Havok_Phantom_t;
    class Havok_Player_Listener_t;
    class Havok_Rigid_Body_t;
    class Havok_Trigger_Volume_t;

    class Havok_Player_t :              // hkpCharacterProxy
        public Havok_Reference_t,       // 00
        public Havok_Entity_Listener_t, // 10
        public Havok_Phantom_Listener_t // 18
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E933E8, // 689957
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Havok_Player_t(); // 00

    public:
        Havok_Array_t<Havok_Collision_t>                collisions;             // 20
        Havok_Array_t<maybe<Havok_Rigid_Body_t*>>       colliding_rigid_bodies; // 30
        Havok_Array_t<maybe<Havok_Phantom_t*>>          phantoms;               // 40
        Havok_Array_t<maybe<Havok_Trigger_Volume_t*>>   trigger_volumes;        // 50
        Havok_Quad_t                                    unk_60;                 // 60
        Havok_Quad_t                                    unk_70;                 // 70
        void*                                           unk_80;                 // 80 (v_table: 0x0172E3E8, has a bunch of ptrs, looks big)
        Float_t                                         dynamic_friction;       // 88
        Float_t                                         static_friction;        // 8C
        Havok_Quad_t                                    unk_90;                 // 90
        Float_t                                         unk_A0;                 // A0
        Float_t                                         unk_A4;                 // A4
        Float_t                                         unk_A8;                 // A8
        Float_t                                         unk_AC;                 // AC
        Float_t                                         unk_B0;                 // B0
        u32                                             unk_B4;                 // B4
        Float_t                                         unk_B8;                 // B8
        Float_t                                         strength;               // BC
        Float_t                                         mass;                   // C0
        u32                                             pad_C4;                 // C4
        Havok_Array_t<maybe<Havok_Player_Listener_t*>>  listeners;              // C8
        Float_t                                         unk_D8;                 // D8
        Float_t                                         unk_DC;                 // DC
        u32                                             unk_E0;                 // E0
        Bool_t                                          unk_E4;                 // E4
        u8                                              pad_E5;                 // E5
        u16                                             pad_E6;                 // E6
        u64                                             pad_E8;                 // E8
    };
    STATIC_ASSERT(sizeof(Havok_Player_t) == 0xF0);

}
