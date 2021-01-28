/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_collidable.h"

namespace doticu_skylib {

    class Havok_Linked_Collidable_t :   // hkpLinkedCollidable
        public Havok_Collidable_t       // 00
    {
    public:
        Byte_t data_070[0x10]; // 70
    };
    STATIC_ASSERT(sizeof(Havok_Linked_Collidable_t) == 0x80);

}
