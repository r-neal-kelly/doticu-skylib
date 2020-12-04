/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib { namespace Virtual {

    class Machine_t;

    class Game_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                SELF = 0x01EC3B78,
            };
            using Enum_t::Enum_t;
        };

        static Game_t* Self();

    public:
        Byte_t      base_classes[0x200];    // 0000
        Machine_t*  machine;                // 0200
    };

}}
