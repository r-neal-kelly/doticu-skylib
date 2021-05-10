/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/calendar.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    Calendar_t& Calendar_t::Self()
    {
        static auto self = *reinterpret_cast
            <Calendar_t**>
            (Game_t::Base_Address() + Offset_e::SELF);

        SKYLIB_ASSERT(self);
        return *self;
    }

}
