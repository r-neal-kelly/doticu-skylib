/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/havok_quad.h"
#include "doticu_skylib/havok_reference.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Havok_Rigid_Body_t;

    class Havok_World_t :           // hkpWorld
        public Havok_Reference_t    // 000
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E927E0, // 689895
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Havok_World_t(); // 0

    public:
        void*                       simulation;                 // 010
        u64                         pad_018;                    // 018
        Havok_Quad_t                gravity;                    // 020
        void*                       fixed_simulation_island;    // 030
        maybe<Havok_Rigid_Body_t*>  fixed_rigid_body;           // 038
        Byte_t                      data_040[0x3F0];            // 040
    };
    STATIC_ASSERT(sizeof(Havok_World_t) == 0x430);

}
