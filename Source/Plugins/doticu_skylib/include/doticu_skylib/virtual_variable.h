/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/form_type.h"

#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_type.h"

namespace doticu_skylib {

    class Actor_t;
    class Alias_Base_t;
    class Faction_t;
    class Form_t;
    class Misc_t;
    class Object_t;
    class Outfit_t;
    class Reference_t;
    class Quest_t;

}

namespace doticu_skylib { namespace Virtual {

    class Array_t;

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
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : _TYPE_
            {
                COPY    = 0x01236E50, // 97509
                DESTROY = 0x01236D10, // 97508
            };
            using Enum_t::Enum_t;
        };

        template <typename Type>
        static Variable_t* Fetch(Type* bsobject, String_t class_name, String_t variable_name);

    public:
        Variable_t();

        Type_e type;
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

        maybe<Script_Type_e> Script_Type();

        Bool_t      Bool();
        Int_t       Int();
        Float_t     Float();
        String_t    String();
        Object_t*   Object();
        Array_t*    Array();
        Array_t*    Object_Array();

        Reference_t*            Reference();
        Quest_t*                Quest();

        void None(Type_e type);
        void Bool(Bool_t value);
        void Int(Int_t value);
        void Float(Float_t value);
        void String(String_t value);
        void Object(Object_t* value);
        void Array(Array_t* value);

        template <typename Probably_Bool_t, enable_if_probably_boolean_t<Probably_Bool_t> = true>
        Probably_Bool_t         Unpack();
        template <typename Integer_32_t, enable_if_integer_32_or_less_t<Integer_32_t> = true>
        Integer_32_t            Unpack();
        template <typename Float_32_t, enable_if_float_32_or_less_t<Float_32_t> = true>
        Float_32_t              Unpack();
        template <typename Scriptable_t, enable_if_pointer_t<Scriptable_t> = true>
        maybe<Scriptable_t>     Unpack();
        template <typename Intrinsic_t, enable_if_not_pointer_or_arithmetic<Intrinsic_t> = true>
        Intrinsic_t             Unpack();

        template <typename Arrayable_t>
        Vector_t<Arrayable_t>   Unpack_Array();
        template <typename Arrayable_t>
        void                    Unpack_Array(Vector_t<Arrayable_t>& results);

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

    class Float_Variable_t : public Variable_t
    {
    public:
        Float_t Value();
        void    Value(Float_t value);
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
#include "doticu_skylib/virtual_class.h"
#include "doticu_skylib/virtual_object.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib { namespace Virtual {

    template <typename Probably_Bool_t, enable_if_probably_boolean_t<Probably_Bool_t>>
    inline Probably_Bool_t Variable_t::Unpack()
    {
        return Bool();
    }

    template <typename Integer_32_t, enable_if_integer_32_or_less_t<Integer_32_t>>
    inline Integer_32_t Variable_t::Unpack()
    {
        return Int();
    }

    template <typename Float_32_t, enable_if_float_32_or_less_t<Float_32_t>>
    inline Float_32_t Variable_t::Unpack()
    {
        return Float();
    }

    template <typename Scriptable_t, enable_if_pointer_t<Scriptable_t>>
    inline maybe<Scriptable_t> Variable_t::Unpack()
    {
        if (type.Is_Object()) {
            if (data.obj) {
                maybe<Script_Type_e> script_type = Script_Type();
                if (script_type) {
                    Handle_Policy_t* handle_policy = Machine_t::Self()->Handle_Policy();
                    if (handle_policy) {
                        return static_cast<Scriptable_t>
                            (handle_policy->Resolve(script_type, data.obj->Handle()));
                    } else {
                        return nullptr;
                    }
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    template <typename Intrinsic_t, enable_if_not_pointer_or_arithmetic<Intrinsic_t>>
    inline Intrinsic_t Variable_t::Unpack()
    {
        STATIC_ASSERT(false);
    }

    template <>
    inline String_t Variable_t::Unpack<String_t>()
    {
        return String();
    }

    template <typename Arrayable_t>
    inline Vector_t<Arrayable_t> Variable_t::Unpack_Array()
    {
        Vector_t<Arrayable_t> results;
        Unpack_Array(results);
        return results;
    }

    template <typename Arrayable_t>
    inline void Variable_t::Unpack_Array(Vector_t<Arrayable_t>& results)
    {
        Array_t* varray = Array();
        if (varray) {
            return varray->Unpack(results);
        }
    }

    template <typename Type_t>
    inline void Variable_t::Pack(Type_t* value)
    {
        if (value) {
            PackHandle(reinterpret_cast<VMValue*>(this),
                       value,
                       Type_t::SCRIPT_TYPE,
                       (*g_skyrimVM)->GetClassRegistry());
        } else {
            None(Class_t::Fetch(Type_t::SCRIPT_TYPE, true));
        }
    }

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
