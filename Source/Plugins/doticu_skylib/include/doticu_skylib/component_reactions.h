/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_form_data.h"
#include "doticu_skylib/enum_form_type.h"
#include "doticu_skylib/forward_list.h"

namespace doticu_skylib {

    class Reaction_t;

    class Reactions_c :     // TESReactionForm
        public Form_Data_c  // 00
    {
    public:
        virtual ~Reactions_c(); // 00

    public:
        List_t<maybe<Reaction_t*>>  reactions;          // 08
        Form_Type_e                 reaction_form_type; // 18
        u8                          pad_19;             // 19
        u16                         pad_1A;             // 1A
        u32                         pad_1C;             // 1C

    public:
        void    Component_Reactions_Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Reactions_c) == 0x20);

}
