/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_handle.h"
#include "doticu_skylib/package.h"
#include "doticu_skylib/reference_handle.h"

namespace doticu_skylib {

    class Package_Dialogue_t :  // DialoguePackage
        public Package_t        // 000
    {
    public:
        virtual ~Package_Dialogue_t();

    public:
        u32                 unk_0E0;    // 0E0
        Reference_Handle_t  unk_0E4;    // 0E4
        Actor_Handle_t      unk_0E8;    // 0E8
        Actor_Handle_t      unk_0EC;    // 0EC
        u64                 unk_0F0;    // 0F0
        u64                 unk_0F8;    // 0F8
    };
    STATIC_ASSERT(sizeof(Package_Dialogue_t) == 0x100);

}
