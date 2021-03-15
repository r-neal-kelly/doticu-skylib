/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/version.h"

namespace doticu_skylib {

    class OS_t
    {
    public:
        static Double_t Microseconds();
        static Double_t Milliseconds();
        static Double_t Seconds();

        static Word_t   Module_Address(maybe<const char*> module_name);
        static size_t   Module_Size(maybe<const char*> module_name);
        static Bool_t   Module_Version(maybe<const char*> module_name, Version_t<u16>& result);
    };

}
