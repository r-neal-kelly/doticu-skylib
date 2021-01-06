/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Grab_Sounds_c : public Form_Data_c // BGSPickupPutdownSounds
    {
    public:
        virtual ~Grab_Sounds_c(); // 0

        void* take_sound;   // 08
        void* leave_sound;  // 10
    };
    STATIC_ASSERT(sizeof(Grab_Sounds_c) == 0x18);

}
