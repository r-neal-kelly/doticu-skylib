/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/dynamic_array.h"

#include "doticu_skylib/havok_entity_base.h"

namespace doticu_skylib {

    class Havok_Rigid_Body_t;

    class Havok_Rigid_Body_Base_t : // bhkRigidBody
        public Havok_Entity_Base_t  // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI    = 0x01E17DC0, // 513967
                V_TABLE = 0x0156A458, // 235519
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Havok_Rigid_Body_Base_t(); // 00

    public:
        Array_t<void*> unk_28; // 28

    public:
        maybe<Havok_Rigid_Body_t*> Rigid_Body();
    };
    STATIC_ASSERT(sizeof(Havok_Rigid_Body_Base_t) == 0x40);

}
