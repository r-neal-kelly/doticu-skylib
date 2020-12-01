/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Sex_e : Enum_t<Int_t>
    {
    public:
        enum : Int_t
        {
            NONE    = -1,
            MALE    = 0,
            FEMALE  = 1,
        };
        using Enum_t::Enum_t;

        static const char* To_String(Sex_e sex_e);
    };

}
