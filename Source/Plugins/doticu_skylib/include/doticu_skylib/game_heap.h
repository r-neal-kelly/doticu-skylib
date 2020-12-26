/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Game_Heap_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                SELF        = 0x01EBD280,
                ALLOCATE    = 0x00C02260,
                DEALLOCATE  = 0x00C02560,
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Game_Heap_t*> Self();

    public:
        maybe<Byte_t*>  Allocate(size_t byte_count);
        void            Deallocate(some<Byte_t*> data);
    };

}
