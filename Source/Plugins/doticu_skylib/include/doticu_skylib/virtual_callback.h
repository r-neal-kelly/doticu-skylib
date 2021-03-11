/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

#include "doticu_skylib/atomic_count.h"
#include "doticu_skylib/main.h"
#include "doticu_skylib/virtual.h"

namespace doticu_skylib { namespace Virtual {

    class Object_t;
    class Variable_t;

    class Callback_i :          // IStackCallbackFunctor
        public Atomic_Count_t   // 08
    {
    private:
        static u64                                  callback_count;
        static std::mutex                           callback_count_lock;
        static std::timed_mutex                     active_callbacks_lock;
        static std::unique_lock<std::timed_mutex>   active_callbacks_locker;

    public:
        static std::unique_lock<std::timed_mutex>   Before_Save();
        static void                                 After_Load();

    public:
        static void*    operator new(size_t byte_count);
        static void     operator delete(void* data);

    public:
        Callback_i(Bool_t do_finish_before_save = true);

    public:
        virtual         ~Callback_i();                          // 00
        virtual void    operator ()(Variable_t* result) = 0;    // 01
        virtual Bool_t  Can_Save()                      = 0;    // 02
        virtual void    Set_Object(Object_t*& object)   = 0;    // 03

    public:
        const Bool_t    do_finish_before_save;  // 0C
        u8              pad_0D;                 // 0D
        u16             pad_0E;                 // 0E
    };
    STATIC_ASSERT(sizeof(Callback_i) == 0x10);

    class Callback_t :
        public Callback_i
    {
    public:
        using Callback_i::Callback_i;

    public:
        virtual void operator ()(Variable_t* result) override
        {
        }

        virtual Bool_t Can_Save() override
        {
            return false;
        }

        virtual void Set_Object(Object_t*& object) override
        {
        }
    };
    STATIC_ASSERT(sizeof(Callback_t) == 0x10);

}}
