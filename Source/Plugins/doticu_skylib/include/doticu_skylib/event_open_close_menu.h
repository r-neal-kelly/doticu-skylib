/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Event_Open_Close_Menu_t   // MenuOpenCloseEvent
    {
    public:
        String_t    menu_name;  // 00
        Bool_t      is_opening; // 08
        u8          pad_09;     // 09
        u16         pad_0A;     // 0A
        u32         pad_0C;     // 0C
    };
    STATIC_ASSERT(sizeof(Event_Open_Close_Menu_t) == 0x10);

}
