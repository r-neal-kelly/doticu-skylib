/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form.h"

namespace doticu_skylib {

    class Object_t :    // TESObject
        public Form_t   // 00
    {
    public:
        virtual         ~Object_t();                    // 00

        virtual void    _3B(void);                      // 3B
        virtual void    _3C(void);                      // 3C
        virtual void    _3D(void);                      // 3D
        virtual void    _3E(void);                      // 3E
        virtual void    _3F(void);                      // 3F
        virtual void    _40(void);                      // 40
        virtual void    _41(void);                      // 41
        virtual void    _42(void);                      // 42
        virtual void    _43(void);                      // 43
        virtual void    _44(void);                      // 44
        virtual u32     Do_Increment_Reference_Count(); // 45
        virtual u32     Do_Decrement_Reference_Count(); // 46
        virtual void    _47(void);                      // 47

    };
    STATIC_ASSERT(sizeof(Object_t) == 0x20);

}
