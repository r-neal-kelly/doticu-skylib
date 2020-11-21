/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/virtual.h"

namespace doticu_skylib { namespace Virtual {

    class Binder_t;
    class Machine_t;
    class Object_t;

    class Handle_Policy_t {
    public:
        static Handle_Policy_t* Self();

    public:
        virtual ~Handle_Policy_t();

        virtual Bool_t Has_Form_Type(Form_Type_e form_type, Raw_Handle_t handle); // 01
        virtual Bool_t Is_Valid(Raw_Handle_t handle); // 02
        virtual Raw_Handle_t Invalid_Handle(); // 03
        virtual Raw_Handle_t Handle(Form_Type_e form_type, const void* form); // 04
        virtual void _05(void); // 05
        virtual void _06(void); // 06
        virtual void _07(void); // 07
        virtual void _08(void); // 08
        virtual void _09(void); // 09
        virtual void Release(Raw_Handle_t handle); // 0A
        virtual void _0B(void); // 0B
    };

    class Bind_Policy_t {
    public:
        static Bind_Policy_t* Self();

    public:
        virtual ~Bind_Policy_t();

        void Bind_Object(Object_t*& object, Raw_Handle_t handle);
        void Unbind_Object(Object_t*& object);

        Machine_t* machine; // 08
        Binder_t* binder; // 10
    };

}}
