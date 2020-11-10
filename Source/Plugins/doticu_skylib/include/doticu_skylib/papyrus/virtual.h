/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/papyrus.h"
#include "doticu_skylib/papyrus/handle.h"
#include "doticu_skylib/papyrus/variable.h"

namespace doticu_skylib { namespace Papyrus {

    class Handle_Policy_t;
    class Object_Policy_t;
    class Virtual_Arguments_i;
    class Virtual_Callback_i;

    class Virtual_Machine_t {
    public:
        static Virtual_Machine_t* Self();

    public:
        virtual ~Virtual_Machine_t(); // 00

        virtual void _01(void); // 01
        virtual void _02(void); // 02
        virtual void _03(void); // 03
        virtual void _04(void); // 04
        virtual void _05(void); // 05
        virtual void _06(void); // 06
        virtual void _07(void); // 07
        virtual void _08(void); // 08
        virtual Bool_t Load_Class_Info(String_t* class_name, Class_t** info_out); // 09, call Class_Info_t Free() after use
        virtual Bool_t Load_Class_Info2(Form_Type_t form_type, Class_t** info_out); // 0A, call Class_Info_t Free() after use
        virtual Bool_t Class_Info(String_t* class_name, Class_t** info_out); // 0B, call Class_Info_t Free() after use
        virtual Bool_t Class_Info2(Form_Type_t form_type, Class_t** info_out); // 0C, call Class_Info_t Free() after use
        virtual Bool_t Type_ID(String_t* class_name, Form_Type_t* form_type_out); // 0D
        virtual void _0E(void); // 0E
        virtual void _0F(void); // 0F
        virtual void _10(void); // 10
        virtual void _11(void); // 11
        virtual void _12(void); // 12
        virtual void _13(void); // 13
        virtual void _14(void); // 14
        virtual Bool_t Create_Object2(String_t* class_name, Object_t** object_out); // 15
        virtual Bool_t Create_Array(Type_t* type, UInt32 count, Array_t** array_out); // 16, SKSE has Variable_t* for first arg?
        virtual void _17(void); // 17
        virtual Bool_t Bind_Function(IFunction* function); // 18
        virtual void _19(void); // 19
        virtual void _1A(void); // 1A
        virtual void For_Each_Object(Handle_t handle, IForEachScriptObjectFunctor* functor); // 1B
        virtual Bool_t Find_Bound_Object(Handle_t handle, String_t class_name, Object_t** object_out); // 1C
        virtual void _1D(void); // 1D
        virtual void _1E(void); // 1E
        virtual Bool_t Cast_Object(Object_t** object_in, Class_t** cast_to, Object_t** object_out); // 1F
        virtual void _20(void); // 20
        virtual void _21(void); // 21
        virtual void _22(void); // 22
        virtual void _23(void); // 23
        virtual void Send_Event(Handle_t handle, String_t* event_name, IFunctionArguments* arguments); // 24
        virtual void _25(void); // 25
        virtual Bool_t Call_Global(String_t* class_name, String_t* function_name, Virtual_Arguments_i* arguments, Virtual_Callback_i** callback); // 26
        virtual void _27(void); // 27
        virtual Bool_t Call_Method2(Handle_t handle, String_t* class_name, String_t* function_name, Virtual_Arguments_i* arguments, Virtual_Callback_i** callback); // 28
        virtual void _29(void); // 29
        virtual void _2A(void); // 2A
        virtual void Return_Latent_Function(Stack_ID_t stack_id, Variable_t* return_variable); // 2B
        virtual void _2C(void); // 2C
        virtual Handle_Policy_t* Handle_Policy(); // 2D
        virtual void _2E(void); // 2E
        virtual Object_Policy_t* Object_Policy(); // 2F

        template <typename BSObject>
        void Send_Event(BSObject* object, String_t event_name, IFunctionArguments* arguments);
        template <typename BSObject>
        void Send_Event(BSObject* object, String_t event_name);

        Bool_t Call_Global(String_t class_name,
                           String_t function_name,
                           Virtual_Arguments_i* arguments = nullptr,
                           Virtual_Callback_i** callback = nullptr);
        Bool_t Call_Method(Handle_t handle,
                           String_t class_name,
                           String_t function_name,
                           Virtual_Arguments_i* arguments = nullptr,
                           Virtual_Callback_i** callback = nullptr);

        Int_t Count_Objects(Handle_t handle);
        Bool_t Has_Object(Handle_t handle);

        Form_Type_t Form_Type(String_t class_name);
    };

    class Virtual_Arguments_i {
    public:
        struct Arguments_t {
            UInt32 unk00; // 00
            UInt32 unk04; // 04
            Variable_t* variables; // 08
            UInt64 unk08; // 10
            UInt32 count; // 18

            Bool_t Resize(UInt32 count);
            Variable_t* At(UInt32 idx);
        };
        STATIC_ASSERT(sizeof(Arguments_t) == 0x20);

        virtual ~Virtual_Arguments_i() = default; // 00

        virtual Bool_t operator()(Arguments_t* arguments) = 0; // 01
    };
    STATIC_ASSERT(sizeof(Virtual_Arguments_i) == 0x8);

    class Virtual_Arguments_t : public Virtual_Arguments_i {
    public:
        virtual Bool_t operator()(Arguments_t* arguments) override
        {
            return true;
        } 
    };
    STATIC_ASSERT(sizeof(Virtual_Arguments_i) == 0x8);

    class Virtual_Callback_i {
    public:
        UInt32 ref_count = 0; // 00
        // void* _vtbl; // 04 (I think)
        UInt32 pad_04; // 0C

        virtual ~Virtual_Callback_i() = default; // 00

        virtual void operator()(Variable_t* result) = 0; // 01
        virtual Bool_t Can_Save() = 0; // 02
        virtual void Set_Object(Object_t** object) = 0; // 03
    };
    STATIC_ASSERT(sizeof(Virtual_Callback_i) == 0x10);

    class Virtual_Callback_t : public Virtual_Callback_i {
    public:
        virtual void operator()(Variable_t* result) override
        {

        };

        virtual Bool_t Can_Save() override
        {
            return false;
        }

        virtual void Set_Object(Object_t** object) override
        {

        }
    };
    STATIC_ASSERT(sizeof(Virtual_Callback_i) == 0x10);

    class Virtual_Binder_t {
    public:
        virtual ~Virtual_Binder_t(); // 00

        virtual Handle_t Bound_Handle(Object_t*& object); // 01
        virtual Bool_t Can_Bind_Class_To_Handle(String_t& class_name, Handle_t handle); // 02
        virtual void Bind_Object(Object_t*& object, Handle_t handle, Bool_t unk_bool); // 03
        virtual void Bind_Object2(Object_t*& object, Handle_t handle, Bool_t unk_bool); // 04 (not sure what this does differently)
        virtual void Unbind_All_Objects(Handle_t handle); // 05
        virtual void Unbind_All_Objects2(Handle_t handle); // 06 (not sure what this does differently)
        virtual void Unbind_All_Objects3(Handle_t handle); // 07 (this one may also delete stuff for us?)
        virtual void Unbind_Object(Object_t*& object); // 08
        virtual void Create_Object(String_t& class_name, UInt32 property_count, Object_t** object_out); // 09
        virtual void Initialize_Object_Properties(Object_t*& object, void* unk_property, Bool_t unk_bool); // 0A
    };

}}
