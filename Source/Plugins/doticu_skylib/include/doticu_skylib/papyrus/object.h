/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/papyrus.h"
#include "doticu_skylib/papyrus/handle.h"
#include "doticu_skylib/papyrus/variable.h"
#include "doticu_skylib/papyrus/class.h"

namespace doticu_skylib { namespace Papyrus {

    class Object_t {
    public:
        template <typename Type>
        static Object_t* Fetch(Type* instance, String_t class_name);
        template <typename Type>
        static Object_t* Create(Type* instance, String_t class_name);
        template <typename Type>
        static Object_t* Create(Type* instance, Class_t* class_info);

        UInt64 unk_00; // 00
        Class_t* info; // 08
        String_t unk_10; // 10
        void* unk_18; // 18
        volatile Handle_t handle; // 20
        volatile SInt32 lock; // 28
        UInt32 pad_2C; // 2C
        //Variable_t variables[0]; // 30

        void Destroy();
        void Increment_Lock();
        UInt32 Decrement_Lock();

        Handle_t Handle();
        Variable_t* Property(String_t property_name);
        Variable_t* Variable(String_t variable_name);
        Variable_t* Variables();

        void Log_Variables();
    };
    STATIC_ASSERT(sizeof(Object_t) == 0x30);

}}
