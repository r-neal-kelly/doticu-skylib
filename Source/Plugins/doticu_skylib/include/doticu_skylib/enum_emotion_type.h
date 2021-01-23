/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Emotion_Type_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            NEUTRAL     = 0,
            ANGER       = 1,
            DISGUST     = 2,
            FEAR        = 3,
            SAD         = 4,
            HAPPY       = 5,
            SURPRISE    = 6,
            PUZZLED     = 7,
        };
        using Enum_t::Enum_t;
    };

}
