/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ai_location_handle.h"

namespace doticu_skylib {

    class AI_Target_Handle_t:       // IAITarget
        public AI_Location_Handle_t // 0
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E230D0, // 685601
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~AI_Target_Handle_t(); // 00
    };
    STATIC_ASSERT(sizeof(AI_Target_Handle_t) == 0x8);

}
