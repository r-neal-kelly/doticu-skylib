/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class XData_t;

    class XList_t {
    public:
        class Presence_Bits_t {

        };

    public:
        XData_t* xdatas;
        Presence_Bits_t* presence;
        BSReadWriteLock lock;
    };
    STATIC_ASSERT(sizeof(XList_t) == 0x18);

}
