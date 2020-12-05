/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Quest_Objective_State_e : Enum_t<u8>
    {
    public:
        enum : u8
        {
            DORMANT                 = 0,
            DISPLAYED               = 1,
            COMPLETED               = 2,
            COMPLETED_AND_DISPLAYED = 3,
            FAILED                  = 4,
            FAILED_AND_DISPLAYED    = 5,
        };
        using Enum_t::Enum_t;

        static const char* To_String(Quest_Objective_State_e quest_objective_state_e);
    };

}
