/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_reference_base.h"

namespace doticu_skylib {

    class Havok_World_t;

    class Havok_Saveable_Base_t :       // bhkSerializable
        public Havok_Reference_Base_t   // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E1AE50, // 685161
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual                 ~Havok_Saveable_Base_t();   // 00

        // Havok_Saveable_Base_t
        virtual Havok_World_t*  Get_World();                // 27
        virtual void            _28(void);                  // 28
        virtual void            _29(void);                  // 29
        virtual void            _2A(void);                  // 2A
        virtual void            _2B(void);                  // 2B
        virtual void            _2C(void);                  // 2C
        virtual void            _2D(void);                  // 2D
        virtual void            _2E(void);                  // 2E
        virtual void            _2F(void);                  // 2F
        virtual void            _30(void);                  // 30
        virtual void            _31(void);                  // 31

    public:
        void* unk_18; // 18
    };
    STATIC_ASSERT(sizeof(Havok_Saveable_Base_t) == 0x20);

}
