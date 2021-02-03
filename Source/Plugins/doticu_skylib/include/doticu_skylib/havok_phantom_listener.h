/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Havok_Phantom_Listener_t // hkpPhantomListener
    {
    public:
        virtual ~Havok_Phantom_Listener_t(); // 0
    };
    STATIC_ASSERT(sizeof(Havok_Phantom_Listener_t) == 0x8);

}
