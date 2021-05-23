/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Animation_Updater_i
    {
    public:
        virtual ~Animation_Updater_i();
    };
    STATIC_ASSERT(sizeof(Animation_Updater_i) == 0x8);

    class Animation_Graphs_t
    {
    public:
        virtual ~Animation_Graphs_t();  // 00

        virtual void _01(void);         // 01
        virtual void _02(void);         // 02
        virtual void _03(void);         // 03
        virtual void _04(void);         // 04
        virtual void _05(void);         // 05
        virtual void _06(void);         // 06
        virtual void _07(void);         // 07
        virtual void _08(void);         // 08
        virtual void _09(void);         // 09
        virtual void _0A(void);         // 0A
        virtual void _0B(void);         // 0B
        virtual void _0C(void);         // 0C
        virtual void _0D(void);         // 0D
        virtual void _0E(void);         // 0E
        virtual void _0F(void);         // 0F
        virtual void _10(void);         // 10
        virtual void _11(void);         // 11
        virtual void _12(void);         // 12
    };
    STATIC_ASSERT(sizeof(Animation_Graphs_t) == 0x8);

}
