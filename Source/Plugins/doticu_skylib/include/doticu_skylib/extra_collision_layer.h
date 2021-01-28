/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

#include "doticu_skylib/enum_collision_layer_type.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Collision_Layer_x : public Data_x // ExtraCollisionData
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::COLLISION_LAYER,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152C940,
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Collision_Layer_x*> Create();
        static some<Collision_Layer_x*> Create(Collision_Layer_Type_e collision_layer_type);
        static void                     Destroy(some<Collision_Layer_x*> collision_layer_x);

    public:
        virtual         ~Collision_Layer_x();                       // 0

        virtual u8      Get_Type()                      override;   // 1
        virtual Bool_t  Isnt_Equal(const Data_x* other) override;   // 2

    public:
        maybe<Collision_Layer_Type_e*> collision_layer_type; // 10

    public:
        Collision_Layer_Type_e  Collision_Layer_Type();
        void                    Collision_Layer_Type(Collision_Layer_Type_e collision_layer_type);

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Collision_Layer_x) == 0x18);

}
