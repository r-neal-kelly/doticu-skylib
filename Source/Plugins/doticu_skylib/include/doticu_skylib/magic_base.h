/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/dynamic_array.h"

namespace doticu_skylib {

    class Magic_Effect_t;
    class Magic_Effect_Instance_t;

    class Magic_Base_t :        // MagicItem
        public Bound_Object_t,  // 00
        public Name_c,          // 30
        public Keywords_c       // 40
    {
    public:
        virtual ~Magic_Base_t(); // 0

    public:
        Array_t<maybe<Magic_Effect_Instance_t*>>    magic_effect_instances;     // 58
        s32                                         hostile_magic_effect_count; // 70
        u32                                         pad_74;                     // 74
        maybe<Magic_Effect_t*>                      magic_effect_template;      // 78
        u32                                         unk_80;                     // 80
        u32                                         pad_84;                     // 84
        void*                                       unk_88;                     // 88

    public:
        Vector_t<some<Magic_Effect_t*>> Magic_Effects();
        void                            Magic_Effects(Vector_t<some<Magic_Effect_t*>>& results);

        Bool_t                          Can_Damage_Health();

    public:
        void    Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Magic_Base_t) == 0x90);

}
