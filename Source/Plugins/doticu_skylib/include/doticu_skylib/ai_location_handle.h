/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class AI_Location_t;            // IAIWorldLocation
    class AI_Location_Context_t;    // AIWorldLocationContext

    class AI_Location_Handle_t  // IAIWorldLocationHandle
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E230A0, // 685600
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual         ~AI_Location_Handle_t();    // 00

        virtual void    _01(void);                  // 01
        virtual void    _02(void);                  // 02
        virtual void    _03(void);                  // 03
    };
    STATIC_ASSERT(sizeof(AI_Location_Handle_t) == 0x8);

}
