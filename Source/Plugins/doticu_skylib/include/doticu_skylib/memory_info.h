/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Memory_Info_Snapshot_t;

    class Memory_Info_i // IMemoryStoreBase
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E97FF8, // 690280
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual         ~Memory_Info_i();                                               // 0
        virtual size_t  Get_Info_Block_Size(const void* block) const            = 0;    // 1
        virtual void    Get_Info_Snaphot(Memory_Info_Snapshot_t& result) const  = 0;    // 2
        virtual Bool_t  Has_Info_Block(const void* block) const                 = 0;    // 3
    };
    STATIC_ASSERT(sizeof(Memory_Info_i) == 0x8);

}
