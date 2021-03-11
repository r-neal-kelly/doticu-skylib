/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Main_t
    {
    public:
        static void Initialize();
        static void Before_Save();
        static void After_Load();
    };

}
