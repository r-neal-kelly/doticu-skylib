/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Package_Override_c : public Form_Data_c // BGSOverridePackCollection
    {
    public:
        virtual ~Package_Override_c(); // 0

        void*   spectator_overrides;        // 08
        void*   observe_corpse_overrides;   // 10
        void*   guard_overrides;            // 18
        void*   combat_overrides;           // 20
    };
    STATIC_ASSERT(sizeof(Package_Override_c) == 0x28);

}
