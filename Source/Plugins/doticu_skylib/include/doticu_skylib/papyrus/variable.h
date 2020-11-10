/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/alias.h"
#include "doticu_skylib/papyrus.h"
#include "doticu_skylib/papyrus/type.h"

namespace doticu_skylib { namespace Papyrus {

    class Object_t;
    class Array_t;

    class Variable_t {
    public:
        static Registry_t* Registry();
        static Policy_t* Policy();

        template <typename Type>
        static Variable_t* Fetch(Type* bsobject,
                                 String_t class_name,
                                 String_t variable_name);
    public:
        Variable_t();

        Type_t type;
        union Variable_u {
            Variable_u();

            void* ptr;
            Bool_t b;
            Int_t i;
            Float_t f;
            String_t str;
            Object_t* obj;
            Array_t* arr;
        } data;

        void Destroy();
        void Copy(Variable_t* other);

        Bool_t Is_None();
        Bool_t Is_Bool();
        Bool_t Is_Int();
        Bool_t Is_Float();
        Bool_t Is_String();
        Bool_t Is_Object();
        Bool_t Is_Array();
        Bool_t Is_None_Array();
        Bool_t Is_Object_Array();
        Bool_t Is_String_Array();
        Bool_t Is_Int_Array();
        Bool_t Is_Float_Array();
        Bool_t Is_Bool_Array();

        Bool_t Has_String();
        Bool_t Has_Object();

        Bool_t Bool();
        Int_t Int();
        Float_t Float();
        String_t String();
        Object_t* Object();
        Array_t* Array();
        Array_t* Object_Array();
        template <typename T>
        T* Resolve(Form_Type_t form_type);
        Form_t* Form();
        Actor_t* Actor();
        Alias_Base_t* Alias();
        Faction_t* Faction();
        Misc_t* Misc();
        Outfit_t* Outfit();
        Reference_t* Reference();
        template <typename Type>
        Vector_t<Type> Vector();

        void None(Type_t type);
        void Bool(Bool_t value);
        void Int(Int_t value);
        void Float(Float_t value);
        void String(String_t value);
        void Object(Object_t* value);
        void Array(Array_t* value);

        template <typename Type>
        void Pack(Type* value, Class_t* class_info);
        template <typename Type>
        void Pack(Type* value);
        template <typename Type>
        void Pack(Vector_t<Type>& values);
    };
    STATIC_ASSERT(sizeof(Variable_t) == 0x10);

}}
