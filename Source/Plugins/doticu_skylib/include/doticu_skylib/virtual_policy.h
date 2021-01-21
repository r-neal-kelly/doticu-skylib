/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "doticu_skylib/virtual.h"

namespace doticu_skylib { namespace Virtual {

    class Binder_t;
    class Machine_t;
    class Object_t;

    class Handle_Policy_t
    {
    public:
        static Handle_Policy_t* Self();

    public:
        virtual                 ~Handle_Policy_t();

        virtual Bool_t          Has_Script_Type(Raw_Script_Type_t script_type, Raw_Handle_t handle);    // 1
        virtual Bool_t          Is_Valid(Raw_Handle_t handle);                                          // 2
        virtual Raw_Handle_t    Invalid_Handle();                                                       // 3
        virtual Raw_Handle_t    Handle(Raw_Script_Type_t script_type, const void* form);                // 4
        virtual void            _05(void);                                                              // 5
        virtual void            _06(void);                                                              // 6
        virtual void            _07(void);                                                              // 7
        virtual void*           Resolve(Raw_Script_Type_t script_type, Raw_Handle_t handle);            // 8
        virtual void            _09(void);                                                              // 9
        virtual void            Release(Raw_Handle_t handle);                                           // A
        virtual void            _0B(void);                                                              // B
    };

    class Object_Policy_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                BIND_OBJECT = 0x0122DAD0,
            };
            using Enum_t::Enum_t;
        };

        static Object_Policy_t* Self();

    public:
        virtual ~Object_Policy_t();

    public:
        Machine_t*  machine;    // 08
        Binder_t*   binder;     // 10

    public:
        void Bind_Object(Object_t** object, Raw_Handle_t handle);
    };

}}
