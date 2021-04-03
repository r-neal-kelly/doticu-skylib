/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/enum_magic_target_flags.h"
#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Active_Magic_Effect_t;
    class Dispelled_Magic_t;
    class Magic_Effect_t;
    class Spell_t;

    class Magic_Target_t // MagicTarget
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                HAS_MAGIC_EFFECT = 0x005530D0, // 33733
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual                                 ~Magic_Target_t();                  // 00
        virtual void                            _01(void);                          // 01
        virtual void                            _02(void);                          // 02
        virtual void                            _03(void);                          // 03
        virtual void                            _04(void);                          // 04
        virtual void                            _05(void);                          // 05
        virtual Bool_t                          Get_Can_Add_Active_Magic_Effects(); // 06
        virtual List_t<Active_Magic_Effect_t*>* Get_Active_Magic_Effects();         // 07
        virtual void                            _08(void);                          // 08
        virtual void                            _09(void);                          // 09
        virtual void                            _0A(void);                          // 0A
        virtual void                            _0B(void);                          // 0B

    public:
        maybe<Dispelled_Magic_t*>   dispelled_magics;   // 08
        Magic_Target_Flags_e        magic_target_flags; // 10
        u8                          pad_11;             // 11
        u16                         pad_12;             // 12
        u32                         pad_14;             // 14

    public:
        Bool_t  Has_Magic_Effect(some<Magic_Effect_t*> magic_effect);
        Bool_t  Has_Magic_Effects(Vector_t<some<Magic_Effect_t*>>& magic_effects);
        Bool_t  Has_Magic_Effects(Vector_t<some<Magic_Effect_t*>>&& magic_effects);
        Bool_t  Has_Magic_Effects(some<Spell_t*> spell);

    public:
        void    Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Magic_Target_t) == 0x18);

}
