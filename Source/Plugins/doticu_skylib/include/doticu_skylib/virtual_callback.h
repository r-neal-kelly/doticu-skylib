/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/atomic_count.h"
#include "doticu_skylib/virtual.h"

namespace doticu_skylib { namespace Virtual {

    class Object_t;
    class Variable_t;

    class Callback_i :          // IStackCallbackFunctor
        public Atomic_Count_t   // 08
    {
    public:
        static void*    operator new(size_t byte_count);
        static void     operator delete(void* data);

    public:
        virtual         ~Callback_i()                   = default;  // 00
        virtual void    operator ()(Variable_t* result) = 0;        // 01
        virtual Bool_t  Can_Save()                      = 0;        // 02
        virtual void    Set_Object(Object_t** object)   = 0;        // 03

    public:
        u32 pad_0C; // 0C
    };
    STATIC_ASSERT(sizeof(Callback_i) == 0x10);

    class Callback_t :
        public Callback_i
    {
    public:
        virtual void operator ()(Variable_t* result) override
        {
        }

        virtual Bool_t Can_Save() override
        {
            return false;
        }

        virtual void Set_Object(Object_t** object) override
        {
        }
    };
    STATIC_ASSERT(sizeof(Callback_t) == 0x10);

}}
