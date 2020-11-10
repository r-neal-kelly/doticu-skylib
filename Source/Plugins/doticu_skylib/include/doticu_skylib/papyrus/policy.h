/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/papyrus.h"
#include "doticu_skylib/papyrus/handle.h"
#include "doticu_skylib/papyrus/object.h"
#include "doticu_skylib/papyrus/virtual.h"

namespace doticu_skylib { namespace Papyrus {

    class Handle_Policy_t {
    public:
        virtual ~Handle_Policy_t();

        virtual Bool_t Has_Type_ID(Form_Type_t form_type, Handle_t handle); // 01
        virtual Bool_t Is_Valid(Handle_t handle); // 02
        virtual Handle_t Invalid_Handle(); // 03
        virtual Handle_t Handle(Form_Type_t form_type, const void* data); // 04
        virtual void _05(void); // 05
        virtual void _06(void); // 06
        virtual void _07(void); // 07
        virtual void _08(void); // 08
        virtual void _09(void); // 09
        virtual void Release(Handle_t handle); // 0A
        virtual void _0B(void); // 0B
    };

    class Object_Policy_t {
    public:
        virtual ~Object_Policy_t();

        void Bind_Object(Object_t*& object, Handle_t handle);
        void Unbind_Object(Object_t*& object);

        Virtual_Machine_t* virtual_machine; // 08
        Virtual_Binder_t* virtual_binder; // 10
    };

}}
