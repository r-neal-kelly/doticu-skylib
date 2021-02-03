/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_actor_controller.h"
#include "doticu_skylib/havok_actor_rigid_body_base.h"
#include "doticu_skylib/havok_actor_rigid_body_listener.h"

namespace doticu_skylib {

    class Havok_Actor_Rigid_Body_Controller_t :     // bhkCharRigidBodyController
        public Havok_Actor_Rigid_Body_Listener_t,   // 000
        public Havok_Actor_Controller_t             // 010
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01EA01B8, // 690822
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Havok_Actor_Rigid_Body_Controller_t(); // 0

    public:
        Havok_Actor_Rigid_Body_Base_t   actor_rigid_body_base;  // 340
        Byte_t                          unk_370[0x20];          // 370 (v_table: 0x017B1CD0)
    };
    STATIC_ASSERT(sizeof(Havok_Actor_Rigid_Body_Controller_t) == 0x390);

}
