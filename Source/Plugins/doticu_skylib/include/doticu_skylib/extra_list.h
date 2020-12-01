/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameTypes.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class List_x
    {
    public:
        class Presence_t
        {
        public:
            static constexpr size_t MAX_FLAGS = 192;

            static Presence_t* Create();

        public:
            Byte_t  flags[MAX_FLAGS >> 3];

            Bool_t  Has(Extra_Type_e type);
            void    Add(Extra_Type_e type);
            void    Remove(Extra_Type_e type);
            void    Clear();
        };
        STATIC_ASSERT(sizeof(Presence_t) == 0x18);

    public:
        Data_x*         xdatas;     // 00
        Presence_t*     presence;   // 08
        BSReadWriteLock lock;       // 10

        void    Validate();

        Bool_t  Has(Extra_Type_e type);
        Data_x* Get(Extra_Type_e type);
        Bool_t  Add(Data_x* xdata);
        Bool_t  Remove(Data_x* xdata);

        template <typename Type_t>
        Bool_t  Has();
        template <typename Type_t>
        Type_t* Get();
    };
    STATIC_ASSERT(sizeof(List_x) == 0x18);

}
