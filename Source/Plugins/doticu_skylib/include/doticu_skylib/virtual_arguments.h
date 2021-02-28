/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/scrap_array.h"

namespace doticu_skylib { namespace Virtual {

    class Variable_t;

    class Arguments_i
    {
    public:
        virtual         ~Arguments_i()                                      = default;  // 00
        virtual Bool_t  operator ()(Scrap_Array_t<Variable_t>* arguments)   = 0;        // 01
    };
    STATIC_ASSERT(sizeof(Arguments_i) == 0x8);

    class Arguments_t :
        public Arguments_i
    {
    public:
        virtual Bool_t operator ()(Scrap_Array_t<Variable_t>* arguments) override
        {
            return true;
        }
    };
    STATIC_ASSERT(sizeof(Arguments_t) == 0x8);

}}
