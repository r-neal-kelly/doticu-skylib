/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Rarity_e : public Enum_t<Int_t>
    {
    public:
        enum : Int_t
        {
            NONE = -1,
            UNIQUE = 0,
            GENERIC = 1,
        };
        using Enum_t::Enum_t;

        static const char* To_String(Rarity_e rarity_e);
    };

}
