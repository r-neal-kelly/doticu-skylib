/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Preloadable_c : public Form_Data_c // BGSPreloadable
    {
    public:
        virtual ~Preloadable_c(); // 0
    };
    STATIC_ASSERT(sizeof(Preloadable_c) == 0x8);

}
