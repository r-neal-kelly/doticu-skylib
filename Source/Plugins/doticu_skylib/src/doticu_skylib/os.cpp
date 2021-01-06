/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/os.h"

namespace doticu_skylib {

    Double_t OS_t::Microseconds()
    {
        LARGE_INTEGER frequency;
        LARGE_INTEGER counter;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&counter);

        return (counter.QuadPart * 1000000.0) / frequency.QuadPart;
    }

    Double_t OS_t::Milliseconds()
    {
        return Microseconds() / 1000.0;
    }

    Double_t OS_t::Seconds()
    {
        return Milliseconds() / 1000.0;
    }

}
