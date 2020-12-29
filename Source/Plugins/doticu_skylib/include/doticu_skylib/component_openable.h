/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Openable_c // BGSOpenCloseForm
    {
    public:
        virtual         ~Openable_c();      // 0

        virtual void    Open_Openable();    // 1
        virtual void    Close_Openable();   // 2
        virtual void    _03(void);          // 3
    };
    STATIC_ASSERT(sizeof(Openable_c) == 0x8);

}
