/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/string.h"

#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_handle.h"

namespace doticu_skylib { namespace Virtual {

    // Handle_t should be Raw_Handle_t. fix it!

    class Object_t;

    class Binder_t {
    public:
        virtual ~Binder_t(); // 00

        virtual Handle_t Bound_Handle(Object_t*& object); // 01
        virtual Bool_t Can_Bind_Class_To_Handle(String_t& class_name, Handle_t handle); // 02
        virtual void Bind_Object(Object_t*& object, Handle_t handle, Bool_t unk_bool); // 03
        virtual void Bind_Object2(Object_t*& object, Handle_t handle, Bool_t unk_bool); // 04 (not sure what this does differently)
        virtual void Unbind_All_Objects(Handle_t handle); // 05
        virtual void Unbind_All_Objects2(Handle_t handle); // 06 (not sure what this does differently)
        virtual void Unbind_All_Objects3(Handle_t handle); // 07 (this one may also delete stuff for us?)
        virtual void Unbind_Object(Object_t*& object); // 08
        virtual void Create_Object(String_t& class_name, u32 property_count, Object_t** object_out); // 09
        virtual void Initialize_Object_Properties(Object_t*& object, void* unk_property, Bool_t unk_bool); // 0A
    };

}}
