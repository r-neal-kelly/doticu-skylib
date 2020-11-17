/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/virtual.h"

namespace doticu_skylib { namespace Virtual {

    class Variable_t;

    class Arguments_i {
    public:
        class Array_t {
        public:
            enum class Offset_e : Word_t {
                RESIZE = 0x00920360, // 53105
            };

        public:
            u32 unk00; // 00
            u32 unk04; // 04
            Variable_t* variables; // 08
            u64 unk08; // 10
            u32 count; // 18

            Bool_t Resize(u32 count);
            Variable_t* At(u32 idx);
        };
        STATIC_ASSERT(sizeof(Array_t) == 0x20);

    public:
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
