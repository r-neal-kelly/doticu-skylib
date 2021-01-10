/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/forward_list.h"

namespace doticu_skylib {

    class Container_Changes_Entry_t;
    class Reference_t;

    class Container_Changes_t
    {
    public:
        List_t<Container_Changes_Entry_t*>* entries;        // 00
        Reference_t*                        owner;          // 08
        Float_t                             total_weight;   // 10
        Float_t                             armor_weight;   // 14
        Bool_t                              has_changed;    // 18
        u8                                  pad_19;         // 19
        u8                                  pad_1A;         // 1A
        u8                                  pad_1B;         // 1B
        u32                                 pad_1C;         // 1C
    };
    STATIC_ASSERT(sizeof(Container_Changes_t) == 0x20);

}
