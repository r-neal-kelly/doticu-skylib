/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"
#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_class.h"
#include "doticu_skylib/virtual_handle.h"

namespace doticu_skylib { namespace Virtual {

    class Class_t;
    class Variable_t;

    class Object_t
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : Word_t
            {
                GET_HANDLE      = 0x01233720, // 97463
                INCREMENT_LOCK  = 0x01234360, // 97468
                DECREMENT_LOCK  = 0x01234410, // 97469
                DESTROY         = 0x01233670, // 97462
            };
            using Enum_t::Enum_t;
        };

    public:
        template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t> = true>
        static maybe<Object_t*> Find(Scriptable_t scriptable, String_t class_name, Bool_t do_decrement);
        template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t> = true>
        static maybe<Object_t*> Find_Or_Create(Scriptable_t scriptable, String_t class_name, Bool_t do_decrement_on_find);
        template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t> = true>
        static maybe<Object_t*> Find_Or_Create(Scriptable_t scriptable, some<Class_t*> v_class, Bool_t do_decrement_on_find);
        template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t> = true>
        static maybe<Object_t*> Find_Or_Create(Scriptable_t scriptable, Bool_t do_decrement_on_find);

    public:
        u64                 unk_00;         // 00
        maybe<Class_t*>     v_class;        // 08
        String_t            unk_10;         // 10
        void*               unk_18;         // 18
        volatile Handle_t   handle;         // 20
        volatile s32        lock;           // 28
        u32                 pad_2C;         // 2C
        //Variable_t        variables[0];   // 30

    public:
        void    Destroy();
        void    Increment_Lock();
        u32     Decrement_Lock();

    public:
        Handle_t    Handle();
        Variable_t* Variables();
        Variable_t* Variable(String_t variable_name);
        Variable_t* Property(String_t property_name); // this does not seem to work yet. use Variable("::" + variable_name + "_var")

        void Log_Variables();
    };
    STATIC_ASSERT(sizeof(Object_t) == 0x30);

}}

#include "doticu_skylib/virtual_machine.h"

namespace doticu_skylib { namespace Virtual {

    template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t>>
    inline maybe<Object_t*> Object_t::Find(Scriptable_t scriptable, String_t class_name, Bool_t do_decrement)
    {
        Handle_t handle(scriptable);
        if (handle.Is_Valid()) {
            Object_t* object = nullptr;
            if (Machine_t::Self()->Do_Find_Bound_Object(handle, class_name, object) && object) {
                if (do_decrement) {
                    object->Decrement_Lock();
                }
                return object;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t>>
    inline maybe<Object_t*> Object_t::Find_Or_Create(Scriptable_t scriptable, String_t v_class_name, Bool_t do_decrement_on_find)
    {
        SKYLIB_ASSERT(v_class_name);

        Handle_t handle(scriptable);
        if (handle.Is_Valid()) {
            some<Machine_t*> machine = Machine_t::Self();
            maybe<Object_t*> object = none<Object_t*>();
            if (machine->Do_Find_Bound_Object(handle, v_class_name, static_cast<Object_t*&>(object)) && object) {
                if (do_decrement_on_find) {
                    object->Decrement_Lock();
                }
                return object;
            } else {
                object = none<Object_t*>();
                if (machine->Do_Create_Object_2(v_class_name, static_cast<Object_t*&>(object)) && object) {
                    machine->Get_Object_Policy_1()->Bind_Object(&object, handle);
                    return object;
                } else {
                    return none<Object_t*>();
                }
            }
        } else {
            return none<Object_t*>();
        }
    }

    template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t>>
    inline maybe<Object_t*> Object_t::Find_Or_Create(Scriptable_t scriptable, some<Class_t*> v_class, Bool_t do_decrement_on_find)
    {
        SKYLIB_ASSERT_SOME(v_class);

        return Find_Or_Create(scriptable, v_class->name, do_decrement_on_find);
    }

    template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t>>
    inline maybe<Object_t*> Object_t::Find_Or_Create(Scriptable_t scriptable, Bool_t do_decrement_on_find)
    {
        some<Script_Type_e> script_type = Script_Type_e::From<Scriptable_t>();
        maybe<Class_t*> v_class = script_type().Class();
        if (v_class) {
            return Find_Or_Create(scriptable, v_class->name, do_decrement_on_find);
        } else {
            return none<Object_t*>();
        }
    }

}}
