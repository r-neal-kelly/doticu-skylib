/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form_type.h"
#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_type.h"

namespace doticu_skylib { namespace Virtual {

    class Actor_t;
    class Alias_Base_t;
    class Form_t;
    class Object_t;
    class Array_t;
    class Reference_t;

    union Variable_u {
        Variable_u();

        void* ptr;
        Bool_t b;
        Int_t i;
        Float_t f;
        String_t str;
        Object_t* obj;
        Array_t* arr;
    };

    class Variable_t {
    public:
        enum class Offset_e : Word_t {
            COPY    = 0x01236E50, // 97509
            DESTROY = 0x01236D10, // 97508
        };

        template <typename Type>
        static Variable_t* Fetch(Type* bsobject, String_t class_name, String_t variable_name);

    public:
        Variable_t();

        Type_t type;
        Variable_u data;

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
        T* Resolve(Form_Type_e form_type);
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
        void Pack(doticu_skylib::Vector_t<Type>& values);
    };
    STATIC_ASSERT(sizeof(Variable_t) == 0x10);

    class Bool_Variable_t : public Variable_t
    {
    public:
        Bool_t  Value();
        void    Value(Bool_t value);
    };
    STATIC_ASSERT(sizeof(Bool_Variable_t) == 0x10);

    class Int_Variable_t : public Variable_t
    {
    public:
        Int_t   Value();
        void    Value(Int_t value);
    };
    STATIC_ASSERT(sizeof(Int_Variable_t) == 0x10);

    class String_Variable_t : public Variable_t
    {
    public:
        String_t    Value();
        void        Value(String_t value);
    };
    STATIC_ASSERT(sizeof(String_Variable_t) == 0x10);

    template <typename T>
    class Array_Variable_t : public Variable_t
    {
    public:
        Array_t*                    Value();
        doticu_skylib::Vector_t<T>  Values();
        void                        Values(doticu_skylib::Vector_t<T>& values);
        void                        Values(doticu_skylib::Vector_t<T>&& values);
    };
    STATIC_ASSERT(sizeof(Array_Variable_t<Int_t>) == 0x10);

    class String_Property_t : public String_Variable_t
    {
    public:
    };
    STATIC_ASSERT(sizeof(String_Property_t) == 0x10);

}}

#include "doticu_skylib/virtual_array.h"

namespace doticu_skylib { namespace Virtual {

    template <typename Type>
    inline void Variable_t::Pack(doticu_skylib::Vector_t<Type>& values)
    {
        PackValue<Type>(reinterpret_cast<VMValue*>(this),
                        reinterpret_cast<VMResultArray<Type>*>(&values),
                        (*g_skyrimVM)->GetClassRegistry());
    }

    template <>
    inline void Variable_t::Pack<String_t>(doticu_skylib::Vector_t<String_t>& values)
    {
        PackValue<BSFixedString>(reinterpret_cast<VMValue*>(this),
                                 reinterpret_cast<VMResultArray<BSFixedString>*>(&values),
                                 (*g_skyrimVM)->GetClassRegistry());
    }

    template <typename T>
    inline Array_t* Array_Variable_t<T>::Value()
    {
        return Array();
    }

    template <typename T>
    inline doticu_skylib::Vector_t<T> Array_Variable_t<T>::Values()
    {
        Array_t* arr = Value();
        if (arr) {
            return arr->Vector<T>();
        } else {
            return doticu_skylib::Vector_t<T>();
        }
    }

    template <typename T>
    inline void Array_Variable_t<T>::Values(doticu_skylib::Vector_t<T>& values)
    {
        Pack<T>(values);
    }

    template <typename T>
    inline void Array_Variable_t<T>::Values(doticu_skylib::Vector_t<T>&& values)
    {
        Pack<T>(values);
    }

}}
