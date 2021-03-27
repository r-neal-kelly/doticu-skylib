/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

#include "doticu_skylib/dynatomic_count.h"

namespace doticu_skylib {

    class Havok_Collidable_Base_t;
    class Havok_Rigid_Body_Base_t;
    class NI_Node_t;
    class NI_RTTI_t;

    class NI_Object_t :             // NiObject
        public Dynatomic_Count_t    // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E14648, // 684825
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~NI_Object_t(); // 00

        // NI_Object_t
        virtual NI_RTTI_t*                  Get_RTTI() const;                   // 02
        virtual NI_Node_t*                  As_NI_Node() const;                 // 03
        virtual void                        _04(void);                          // 04
        virtual void                        _05(void);                          // 05
        virtual void                        _06(void);                          // 06
        virtual void                        _07(void);                          // 07
        virtual void                        _08(void);                          // 08
        virtual void                        _09(void);                          // 09
        virtual void                        _0A(void);                          // 0A
        virtual void                        _0B(void);                          // 0B
        virtual void                        _0C(void);                          // 0C
        virtual void                        _0D(void);                          // 0D
        virtual void                        _0E(void);                          // 0E
        virtual void                        _0F(void);                          // 0F
        virtual void                        _10(void);                          // 10
        virtual void                        _11(void);                          // 11
        virtual Havok_Collidable_Base_t*    As_Havok_Collidable_Base() const;   // 12
        virtual void                        _13(void);                          // 13
        virtual void                        _14(void);                          // 14
        virtual Havok_Rigid_Body_Base_t*    As_Havok_Rigid_Body_Base() const;   // 15
        virtual void                        _16(void);                          // 16
        virtual void                        _17(void);                          // 17
        virtual void                        _18(void);                          // 18
        virtual void                        _19(void);                          // 19
        virtual void                        _1A(void);                          // 1A
        virtual void                        _1B(void);                          // 1B
        virtual void                        _1C(void);                          // 1C
        virtual void                        _1D(void);                          // 1D
        virtual void                        _1E(void);                          // 1E
        virtual void                        _1F(void);                          // 1F
        virtual void                        _20(void);                          // 20
        virtual void                        _21(void);                          // 21
        virtual void                        _22(void);                          // 22
        virtual void                        _23(void);                          // 23
        virtual void                        _24(void);                          // 24

    public:
        void Log_RTTIs(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(NI_Object_t) == 0x10);

}
