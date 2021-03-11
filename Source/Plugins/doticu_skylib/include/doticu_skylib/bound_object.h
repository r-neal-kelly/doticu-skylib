/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/object.h"

namespace doticu_skylib {

    class Voice_Type_t;

    class Bound_Object_t :  // TESBoundObject
        public Object_t     // 00
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E10EB8, // 513852
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual                 ~Bound_Object_t();                          // 00

        virtual void            Set_Voice_Type(Voice_Type_t* voice_type);   // 48
        virtual Voice_Type_t*   Get_Voice_Type() const;                     // 49
        virtual void            _4A(void);                                  // 4A
        virtual void            _4B(void);                                  // 4B
        virtual void            _4C(void);                                  // 4C
        virtual void            _4D(void);                                  // 4D
        virtual void            _4E(void);                                  // 4E
        virtual void            _4F(void);                                  // 4F
        virtual void            _50(void);                                  // 50
        virtual void            _51(void);                                  // 51
        virtual void            _52(void);                                  // 52

    public:
        s16_xyz bound_min;  // 20
        s16_xyz bound_max;  // 26
        u32     pad_2C;     // 2C
    };
    STATIC_ASSERT(sizeof(Bound_Object_t) == 0x30);

}
