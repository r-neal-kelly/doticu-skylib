/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Magic_Effect_t;

    class Magic_Target_t // MagicTarget
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                HAS_MAGIC_EFFECT = 0x005530D0, // 33733
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Magic_Target_t();

    public:
        void*   unk_08; // 08
        u8      unk_10; // 10
        u8      pad_11; // 11
        u16     pad_12; // 12
        u32     pad_14; // 14

    public:
        Bool_t Has_Magic_Effect(some<Magic_Effect_t*> magic_effect);
    };
    STATIC_ASSERT(sizeof(Magic_Target_t) == 0x18);

}
