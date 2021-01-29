/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_collision_layer_type.h"

#include "doticu_skylib/havok_collidable_links.h"
#include "doticu_skylib/havok_reference.h"

namespace doticu_skylib {

    class Havok_Body_t :            // hkpWorldObject
        public Havok_Reference_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E35610, // 686314
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Havok_Body_t(); // 0

    public:
        void*                       world;              // 10
        u64                         unk_18;             // 18
        Havok_Collidable_Links_t    collidable_links;   // 20
        Byte_t                      data_A0[0x30];      // A0

    public:
        Collision_Layer_Type_e  Collision_Layer_Type();
        void                    Collision_Layer_Type(Collision_Layer_Type_e collision_layer_type);
    };
    STATIC_ASSERT(sizeof(Havok_Body_t) == 0xD0);

}
