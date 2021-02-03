/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor.h"

namespace doticu_skylib {

    class Character_t : public Actor_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E39330, // 514043
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Character_t(); // 0

        // Character_t
        virtual void* _128();
        virtual void* _129();
    };
    STATIC_ASSERT(sizeof(Character_t) == 0x2B0);

}
