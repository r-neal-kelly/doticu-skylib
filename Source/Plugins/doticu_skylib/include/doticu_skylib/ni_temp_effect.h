/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_ni_temp_effect_type.h"

#include "doticu_skylib/ni_object.h"

namespace doticu_skylib {

    class Cell_t;
    class NI_3D_t;

    class NI_Temp_Effect_t :    // BSTempEffect
        public NI_Object_t      // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E2EE18, // 686036
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~NI_Temp_Effect_t(); // 00

        // NI_Temp_Effect_t
        virtual void        _25(void);          // 25
        virtual void        _26(void);          // 26
        virtual void        _27(void);          // 27
        virtual void        _28(void);          // 28
        virtual NI_3D_t*    Get_NI_3D() const;  // 29
        virtual void        _2A(void);          // 2A
        virtual void        _2B(void);          // 2B
        virtual u32         Get_Type() const;   // 2C (NI_Temp_Effect_Type_e)
        virtual void        _2D(void);          // 2D
        virtual void        _2E(void);          // 2E
        virtual void        _2F(void);          // 2F
        virtual void        _30(void);          // 30
        virtual void        _31(void);          // 31
        virtual void        _32(void);          // 32
        virtual void        _33(void);          // 33
        virtual void        _34(void);          // 34
        virtual void        _35(void);          // 35

    public:
        Float_t                 life_time;          // 10
        u32                     pad_14;             // 14
        Cell_t*                 cell;               // 18
        Float_t                 age;                // 20
        Bool_t                  is_initialized;     // 24
        u8                      pad_25;             // 25
        u16                     pad_26;             // 26
        NI_Temp_Effect_Type_e   temp_effect_type;   // 28
        u32                     pad_2C;             // 2C
    };
    STATIC_ASSERT(sizeof(NI_Temp_Effect_t) == 0x30);

}
