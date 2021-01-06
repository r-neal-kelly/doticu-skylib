/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class OS_t
    {
    public:
        static Double_t Microseconds();
        static Double_t Milliseconds();
        static Double_t Seconds();
    };

}
