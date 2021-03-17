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

    class Function_i;           // IFunction
    class Object_Iterator_i;    // IForEachScriptObjectFunctor

    class Machine_t
    {
    public:
        static some<Machine_t*> Self();

        template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t> = true>
        static Bool_t           Ready_Scriptable(some<Scriptable_t> scriptable);

    public:
        virtual                         ~Machine_t();                                                                           // 00
        virtual void                    _01(void);                                                                              // 01
        virtual void                    _02(void);                                                                              // 02
        virtual void                    _03(void);                                                                              // 03
        virtual void                    _04(void);                                                                              // 04
        virtual void                    _05(void);                                                                              // 05
        virtual void                    _06(void);                                                                              // 06
        virtual void                    _07(void);                                                                              // 07
        virtual void                    _08(void);                                                                              // 08
        virtual Bool_t                  Do_Find_Or_Load_Class_1(String_t& class_name, Class_t*& result);                        // 09 increments Class_t
        virtual Bool_t                  Do_Find_Or_Load_Class_2(Raw_Script_Type_t script_type, Class_t*& result);               // 0A increments Class_t
        virtual Bool_t                  Do_Find_Class_1(String_t& class_name, Class_t*& result);                                // 0B increments Class_t (not sure about the difference)
        virtual Bool_t                  Do_Find_Class_2(Raw_Script_Type_t script_type, Class_t*& result);                       // 0C increments Class_t ("")
        virtual Bool_t                  Get_Class_Script_Type(String_t& class_name, Raw_Script_Type_t& result);                 // 0D
        virtual void                    _0E(void);                                                                              // 0E
        virtual void                    _0F(void);                                                                              // 0F
        virtual void                    _10(void);                                                                              // 10
        virtual void                    _11(void);                                                                              // 11
        virtual void                    _12(void);                                                                              // 12
        virtual void                    _13(void);                                                                              // 13
        virtual void                    _14(void);                                                                              // 14
        virtual Bool_t                  Do_Create_Object_2(String_t& class_name, Object_t*& result);                            // 15
        virtual Bool_t                  Do_Create_Array_1(Raw_Type_t& type, u32 count, Array_t*& result);                       // 16
        virtual void                    _17(void);                                                                              // 17
        virtual Bool_t                  Do_Bind_Function(Function_i* function);                                                 // 18
        virtual void                    Set_Function_Skips_Frame_Wait_1(const char* class_name,
                                                                        const char* state_name,
                                                                        const char* function_name,
                                                                        Bool_t skips_frame_wait);                               // 19
        virtual void                    Set_Function_Skips_Frame_Wait_2(const char* class_name,
                                                                        const char* function_name,
                                                                        Bool_t skips_frame_wait);                               // 1A
        virtual void                    Do_Iterate_Bound_Objects(Raw_Handle_t handle, Object_Iterator_i& iterator);             // 1B
        virtual Bool_t                  Do_Find_Bound_Object(Raw_Handle_t handle, const char* class_name, Object_t*& result);   // 1C
        virtual void                    _1D(void);                                                                              // 1D
        virtual void                    _1E(void);                                                                              // 1E
        virtual Bool_t                  Do_Cast_Object(const Object_t*& from, const Class_t*& to, Object_t*& result);           // 1F
        virtual void                    _20(void);                                                                              // 20
        virtual void                    _21(void);                                                                              // 21
        virtual void                    _22(void);                                                                              // 22
        virtual void                    _23(void);                                                                              // 23
        virtual void                    Do_Send_Event(Raw_Handle_t handle,
                                                      const String_t& event_name,
                                                      Arguments_i& arguments);                                                  // 24
        virtual void                    _25(void);                                                                              // 25
        virtual Bool_t                  Do_Call_Global(const String_t& class_name,
                                                       const String_t& function_name,
                                                       Arguments_i& arguments,
                                                       Callback_i*& callback);                                                  // 26
        virtual void                    _27(void);                                                                              // 27
        virtual Bool_t                  Do_Call_Method_2(Raw_Handle_t handle,
                                                         const String_t& class_name,
                                                         const String_t& function_name,
                                                         Arguments_i& arguments,
                                                         Callback_i*& callback);                                                // 28
        virtual void                    _29(void);                                                                              // 29
        virtual void                    _2A(void);                                                                              // 2A
        virtual void                    Do_Return_Latent_Function(Raw_Stack_ID_t stack_id, const Variable_t& return_variable);  // 2B
        virtual void                    _2C(void);                                                                              // 2C
        virtual Handle_Policy_t*        Get_Handle_Policy_1();                                                                  // 2D
        virtual const Handle_Policy_t*  Get_Handle_Policy_2() const;                                                            // 2E
        virtual Object_Policy_t*        Get_Object_Policy_1();                                                                  // 2F
        virtual const Object_Policy_t*  Get_Object_Policy_2() const;                                                            // 30

    public:
        Bool_t  Call_Global(String_t class_name,
                            String_t function_name,
                            maybe<Arguments_i*> arguments = nullptr,
                            maybe<Callback_i*> callback = nullptr);
        Bool_t  Call_Global(String_t class_name,
                            String_t function_name,
                            Arguments_i&& arguments,
                            maybe<Callback_i*> callback = nullptr);

        Bool_t  Call_Method(Handle_t handle,
                            String_t class_name,
                            String_t function_name,
                            maybe<Arguments_i*> arguments = nullptr,
                            maybe<Callback_i*> callback = nullptr);
        Bool_t  Call_Method(Handle_t handle,
                            String_t class_name,
                            String_t function_name,
                            Arguments_i&& arguments,
                            maybe<Callback_i*> callback = nullptr);

        void    Send_Event(Handle_t handle,
                           String_t event_name,
                           maybe<Arguments_i*> arguments = nullptr);
        void    Send_Event(Handle_t handle,
                           String_t event_name,
                           Arguments_i&& arguments);

        void    Return_Latent_Function(Stack_ID_t stack_id, const Variable_t& return_variable);
        void    Return_Latent_Function(Stack_ID_t stack_id, const Variable_t&& return_variable);
    };

}}
