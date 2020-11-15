/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    enum class Relation_e : u8
    {
        NONE = static_cast<u8>(-1),

        LOVER = 0,
        ALLY = 1,
        CONFIDANT = 2,
        FRIEND = 3,
        ACQUAINTANCE = 4,
        RIVAL = 5,
        FOE = 6,
        ENEMY = 7,
        ARCHNEMESIS = 8,
    };

}
