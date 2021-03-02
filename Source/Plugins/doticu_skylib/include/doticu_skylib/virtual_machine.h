/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"
#include "doticu_skylib/traits.h"
#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_handle.h"
#include "doticu_skylib/virtual_stack_id.h"
#include "doticu_skylib/virtual_type.h"

namespace doticu_skylib { namespace Virtual {

    class Arguments_i;
    class Array_t;
    class Callback_i;
    class Class_t;
    class Handle_Policy_t;
    class Object_t;
    class Object_Policy_t;
    class Variable_t;

    class Function_i;
    class Object_Iterator_i;

    class Machine_t
    {
    public:
        static some<Machine_t*> Self();

        template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t> = true>
        static Bool_t           Ready_Scriptable(some<Scriptable_t> scriptable);

    public:
        virtual ~Machine_t(); // 00

        virtual void _01(void); // 01
        virtual void _02(void); // 02
        virtual void _03(void); // 03
        virtual void _04(void); // 04
        virtual void _05(void); // 05
        virtual void _06(void); // 06
        virtual void _07(void); // 07
        virtual void _08(void); // 08
        virtual Bool_t Find_Or_Load_Class(String_t& class_name, Class_t*& vclass_out);              // 09 increments reference
        virtual Bool_t Find_Or_Load_Class_2(Raw_Script_Type_t script_type, Class_t*& vclass_out);   // 0A increments reference
        virtual Bool_t Find_Class(String_t& class_name, Class_t*& vclass_out);                      // 0B increments reference
        virtual Bool_t Find_Class_2(Raw_Script_Type_t script_type, Class_t*& vclass_out);           // 0C increments reference
        virtual Bool_t Class_Script_Type(String_t& class_name, Raw_Script_Type_t& script_type_out); // 0D
        virtual void _0E(void); // 0E
        virtual void _0F(void); // 0F
        virtual void _10(void); // 10
        virtual void _11(void); // 11
        virtual void _12(void); // 12
        virtual void _13(void); // 13
        virtual void _14(void); // 14
        virtual Bool_t Create_Object2(String_t* class_name, Object_t** object_out); // 15
        virtual Bool_t Create_Array(Raw_Type_t& type, u32 count, Array_t*& array_out); // 16, SKSE has Variable_t* for first arg? (Create_Array(Variable_t& variable, u32 count, Array_t*& array_out))
        virtual void _17(void); // 17
        virtual Bool_t Bind_Function(Function_i* function); // 18 (IFunction)
        virtual void State_Function_Skips_Frame_Wait(const char* class_name, const char* state_name, const char* function_name, Bool_t doesnt_wait); // 19
        virtual void Function_Skips_Frame_Wait(const char* class_name, const char* function_name, Bool_t doesnt_wait); // 1A
        virtual void Iterate_Objects(Handle_t handle, Object_Iterator_i* iterator); // 1B (IForEachScriptObjectFunctor)
        virtual Bool_t Find_Bound_Object(Handle_t handle, String_t class_name, Object_t** object_out); // 1C
        virtual void _1D(void); // 1D
        virtual void _1E(void); // 1E
        virtual Bool_t Cast_Object(Object_t** object_in, Class_t** cast_to, Object_t** object_out); // 1F
        virtual void _20(void); // 20
        virtual void _21(void); // 21
        virtual void _22(void); // 22
        virtual void _23(void); // 23
        virtual void Send_Event(Handle_t handle, String_t* event_name, Arguments_i* arguments); // 24
        virtual void _25(void); // 25
        virtual Bool_t Call_Global(String_t* class_name, String_t* function_name, Arguments_i* arguments, Callback_i** callback); // 26
        virtual void _27(void); // 27
        virtual Bool_t Call_Method2(Handle_t handle, String_t* class_name, String_t* function_name, Arguments_i* arguments, Callback_i** callback); // 28
        virtual void _29(void); // 29
        virtual void _2A(void); // 2A
        virtual void Return_Latent_Function(Raw_Stack_ID_t stack_id, Variable_t* return_variable); // 2B
        virtual void _2C(void); // 2C
        virtual Handle_Policy_t* Handle_Policy(); // 2D
        virtual void _2E(void); // 2E
        virtual Object_Policy_t* Object_Policy(); // 2F

    public:
        Bool_t  Call_Global(String_t class_name,
                            String_t function_name,
                            Arguments_i* arguments = nullptr,
                            Callback_i** vcallback = nullptr);
        Bool_t  Call_Global(String_t class_name,
                            String_t function_name,
                            maybe<Arguments_i*> varguments = nullptr,
                            maybe<Callback_i*> vcallback = nullptr);

        Bool_t  Call_Method(Handle_t handle,
                            String_t class_name,
                            String_t function_name,
                            Arguments_i* arguments = nullptr,
                            Callback_i** vcallback = nullptr);
        Bool_t  Call_Method(Handle_t handle,
                            String_t class_name,
                            String_t function_name,
                            maybe<Arguments_i*> maybe_varguments = nullptr,
                            maybe<Callback_i*> maybe_vcallback = nullptr);
        Bool_t  Call_Method(Handle_t handle,
                            String_t class_name,
                            String_t function_name,
                            Arguments_i&& varguments,
                            maybe<Callback_i*> maybe_vcallback = nullptr);

        void    Send_Event(Handle_t handle,
                           String_t event_name,
                           maybe<Arguments_i*> maybe_varguments = nullptr);
    };

}}
