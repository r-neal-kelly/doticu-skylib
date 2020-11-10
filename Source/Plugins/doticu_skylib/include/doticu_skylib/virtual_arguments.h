/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/virtual.h"

namespace doticu_skylib { namespace Virtual {

    class Variable_t;

    class Arguments_i {
    public:
        struct Array_t {
            UInt32 unk00; // 00
            UInt32 unk04; // 04
            Variable_t* variables; // 08
            UInt64 unk08; // 10
            UInt32 count; // 18

            Bool_t Resize(UInt32 count);
            Variable_t* At(UInt32 idx);
        };
        STATIC_ASSERT(sizeof(Array_t) == 0x20);

        virtual ~Arguments_i() = default; // 00

        virtual Bool_t operator()(Array_t* arguments) = 0; // 01
    };
    STATIC_ASSERT(sizeof(Arguments_i) == 0x8);

    class Arguments_t : public Arguments_i {
    public:
        virtual Bool_t operator()(Array_t* arguments) override
        {
            return true;
        }
    };
    STATIC_ASSERT(sizeof(Arguments_t) == 0x8);

}}
