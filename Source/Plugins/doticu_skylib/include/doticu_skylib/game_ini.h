/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameSettings.h" // temp until we fully develop our Game_INI_t

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Game_INI_t
    {
    public:
        static u32 INI_u32(const char* label) // this is prob. temp until we set up templates
        {
            Setting* setting = GetINISetting(label);
            if (setting && setting->GetType() == Setting::kType_Integer) {
                return setting->data.u32;
            } else {
                return 0;
            }
        }
    };

}
