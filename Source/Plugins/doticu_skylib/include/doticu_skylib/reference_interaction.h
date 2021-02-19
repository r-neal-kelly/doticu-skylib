/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"
#include "doticu_skylib/reference_handle.h"
#include "doticu_skylib/sync_object.h"

namespace doticu_skylib {

    class Reference_t;

    class Reference_Interaction_t : // RefrInteraction
        public Sync_Object_t        // 00
    {
    public:
        virtual ~Reference_Interaction_t(); // 0

    public:
        Reference_Handle_t  interactor_handle_a;    // 10
        Reference_Handle_t  interactor_handle_b;    // 14
        Bool_t              is_in_sync;             // 18
        u8                  pad_19;                 // 19
        u16                 pad_1A;                 // 1A
        u32                 pad_1C;                 // 1C

    public:
        maybe<Reference_t*> Interactor_A();
        maybe<Reference_t*> Interactor_B();
    };
    STATIC_ASSERT(sizeof(Reference_Interaction_t) == 0x20);

}
