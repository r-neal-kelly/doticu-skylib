/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/virtual_array.h"
#include "doticu_skylib/virtual_class.h"
#include "doticu_skylib/virtual_handle.h"
#include "doticu_skylib/virtual_object.h"
#include "doticu_skylib/virtual_policy.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib { namespace Virtual {

    inline Bool_t Variable_t::Is_None()         { return type.Is_None(); }
    inline Bool_t Variable_t::Is_Bool()         { return type.Is_Bool(); }
    inline Bool_t Variable_t::Is_Int()          { return type.Is_Int(); }
    inline Bool_t Variable_t::Is_Float()        { return type.Is_Float(); }
    inline Bool_t Variable_t::Is_String()       { return type.Is_String(); }
    inline Bool_t Variable_t::Is_Object()       { return type.Is_Object(); }
    inline Bool_t Variable_t::Is_Array()        { return type.Is_Array(); }
    inline Bool_t Variable_t::Is_None_Array()   { return type.Is_None_Array(); }
    inline Bool_t Variable_t::Is_Bool_Array()   { return type.Is_Bool_Array(); }
    inline Bool_t Variable_t::Is_Int_Array()    { return type.Is_Int_Array(); }
    inline Bool_t Variable_t::Is_Float_Array()  { return type.Is_Float_Array(); }
    inline Bool_t Variable_t::Is_String_Array() { return type.Is_String_Array(); }
    inline Bool_t Variable_t::Is_Object_Array() { return type.Is_Object_Array(); }

    inline Object_t* Variable_t::Object()
    {
        if (type.Is_Object()) {
            return data.obj;
        } else {
            return nullptr;
        }
    }

    inline Array_t* Variable_t::Array()
    {
        if (type.Is_Array()) {
            return data.arr;
        } else {
            return nullptr;
        }
    }

    inline maybe<Script_Type_e> Variable_t::Script_Type()
    {
        Class_t* vclass = type.Class();
        if (vclass) {
            return vclass->Script_Type();
        } else {
            return none<Script_Type_e>();
        }
    }

    template <typename Boolable_t, enable_if_virtual_bool_t<Boolable_t>>
    inline Boolable_t Variable_t::Unpack()
    {
        if (type.Is_Bool()) {
            return data.b;
        } else {
            return false;
        }
    }

    template <typename Intable_t, enable_if_virtual_int_t<Intable_t>>
    inline Intable_t Variable_t::Unpack()
    {
        if (type.Is_Int()) {
            return data.i;
        } else {
            return 0;
        }
    }

    template <typename Floatable_t, enable_if_virtual_float_t<Floatable_t>>
    inline Floatable_t Variable_t::Unpack()
    {
        if (type.Is_Float()) {
            return data.f;
        } else {
            return 0.0;
        }
    }

    template <typename Stringable_t, enable_if_virtual_string_t<Stringable_t>>
    inline Stringable_t Variable_t::Unpack()
    {
        if (type.Is_String()) {
            return data.str;
        } else {
            return "";
        }
    }

    template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t>>
    inline Scriptable_t Variable_t::Unpack()
    {
        if (type.Is_Object() && data.obj) {
            return data.obj->Handle().Resolve<Scriptable_t>();
        } else {
            return nullptr;
        }
    }

    template <typename Scriptable_t, enable_if_maybe_virtual_script_t<Scriptable_t>>
    inline Scriptable_t Variable_t::Unpack()
    {
        return Unpack<typename Scriptable_t::value_type*>();
    }

    template <typename Scriptable_t, enable_if_some_virtual_script_t<Scriptable_t>>
    inline Scriptable_t Variable_t::Unpack()
    {
        return Unpack<typename Scriptable_t::value_type*>();
    }

    template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t>>
    inline Arrayable_t Variable_t::Unpack()
    {
        Arrayable_t results;
        Unpack(results);
        return results;
    }

    template <typename Boolable_t, enable_if_virtual_bool_t<Boolable_t>>
    inline void Variable_t::Unpack(Boolable_t& result)
    {
        result = Unpack<Boolable_t>();
    }

    template <typename Intable_t, enable_if_virtual_int_t<Intable_t>>
    inline void Variable_t::Unpack(Intable_t& result)
    {
        result = Unpack<Intable_t>();
    }

    template <typename Floatable_t, enable_if_virtual_float_t<Floatable_t>>
    inline void Variable_t::Unpack(Floatable_t& result)
    {
        result = Unpack<Floatable_t>();
    }

    template <typename Stringable_t, enable_if_virtual_string_t<Stringable_t>>
    inline void Variable_t::Unpack(Stringable_t& result)
    {
        result = Unpack<Stringable_t>();
    }

    template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t>>
    inline void Variable_t::Unpack(Scriptable_t& result)
    {
        result = Unpack<Scriptable_t>();
    }

    template <typename Scriptable_t, enable_if_maybe_virtual_script_t<Scriptable_t>>
    inline void Variable_t::Unpack(Scriptable_t& result)
    {
        result = Unpack<typename Scriptable_t::value_type*>();
    }

    template <typename Scriptable_t, enable_if_some_virtual_script_t<Scriptable_t>>
    inline void Variable_t::Unpack(Scriptable_t& result)
    {
        result = Unpack<typename Scriptable_t::value_type*>();
    }

    template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t>>
    inline void Variable_t::Unpack(Arrayable_t& results)
    {
        Array_t* varray = Array();
        if (varray) {
            return varray->Unpack<Arrayable_t>(results);
        }
    }

    template <typename Voidable_t, enable_if_void_t<Voidable_t>>
    inline void Variable_t::Pack()
    {
        Destroy();
        this->type = Type_e::NONE;
        this->data.ptr = nullptr;
    }

    template <typename Boolable_t, enable_if_virtual_bool_t<Boolable_t>>
    inline void Variable_t::Pack(const Boolable_t& value)
    {
        Destroy();
        type = Type_e::BOOL;
        data.b = value;
    }

    template <typename Intable_t, enable_if_virtual_int_t<Intable_t>>
    inline void Variable_t::Pack(const Intable_t& value)
    {
        Destroy();
        type = Type_e::INT;
        data.i = value;
    }

    template <typename Floatable_t, enable_if_virtual_float_t<Floatable_t>>
    inline void Variable_t::Pack(const Floatable_t& value)
    {
        Destroy();
        type = Type_e::FLOAT;
        data.f = value;
    }

    template <typename Stringable_t, enable_if_virtual_string_t<Stringable_t>>
    inline void Variable_t::Pack(const Stringable_t& value)
    {
        Destroy();
        type = Type_e::STRING;
        data.str.Write(value);
    }

    template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t>>
    inline void Variable_t::Pack(const Scriptable_t& value)
    {
        Destroy();

        some<Script_Type_e> script_type = Script_Type_e::From<Scriptable_t>();
        type = script_type();
        if (value) {
            maybe<Object_t*> object = Object_t::Find_Or_Create(value, false);
            if (object) {
                data.obj = object();
            }
        }
    }

    template <typename Scriptable_t, enable_if_maybe_virtual_script_t<Scriptable_t>>
    inline void Variable_t::Pack(const Scriptable_t& value)
    {
        Pack<typename Scriptable_t::value_type*>(value());
    }

    template <typename Scriptable_t, enable_if_some_virtual_script_t<Scriptable_t>>
    inline void Variable_t::Pack(const Scriptable_t& value)
    {
        SKYLIB_ASSERT_SOME(value);

        Pack<typename Scriptable_t::value_type*>(value());
    }

    template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t>>
    inline void Variable_t::Pack(const Arrayable_t& values)
    {
        Destroy();

        this->type = Type_e::From<Arrayable_t>();
        size_t value_count = values.size();
        if (value_count > 0) {
            Array_t* varray = nullptr;
            Type_e item_type = Type_e::From<Arrayable_t::value_type>();
            if (Machine_t::Self()->Do_Create_Array_1(item_type.mangled, value_count, varray) && varray) {
                varray->Pack(values);
                this->data.arr = varray;
            }
        }
    }

    template <typename Boolable_t, enable_if_virtual_bool_t<Boolable_t>>
    inline void Variable_t::Pack(Boolable_t&& value)
    {
        Destroy();
        type = Type_e::BOOL;
        data.b = std::move(value);
    }

    template <typename Intable_t, enable_if_virtual_int_t<Intable_t>>
    inline void Variable_t::Pack(Intable_t&& value)
    {
        Destroy();
        type = Type_e::INT;
        data.i = std::move(value);
    }

    template <typename Floatable_t, enable_if_virtual_float_t<Floatable_t>>
    inline void Variable_t::Pack(Floatable_t&& value)
    {
        Destroy();
        type = Type_e::FLOAT;
        data.f = std::move(value);
    }

    template <typename Stringable_t, enable_if_virtual_string_t<Stringable_t>>
    inline void Variable_t::Pack(Stringable_t&& value)
    {
        Pack<Stringable_t>(value);
    }

    template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t>>
    inline void Variable_t::Pack(Scriptable_t&& value)
    {
        Pack<Scriptable_t>(value);
    }

    template <typename Scriptable_t, enable_if_maybe_virtual_script_t<Scriptable_t>>
    inline void Variable_t::Pack(Scriptable_t&& value)
    {
        Pack<typename Scriptable_t::value_type*>(value());
    }

    template <typename Scriptable_t, enable_if_some_virtual_script_t<Scriptable_t>>
    inline void Variable_t::Pack(Scriptable_t&& value)
    {
        Pack<typename Scriptable_t::value_type*>(value());
    }

    template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t>>
    inline void Variable_t::Pack(Arrayable_t&& values)
    {
        Pack<Arrayable_t>(values);
    }

    inline Bool_t       Variable_t::Bool()                          { return Unpack<Bool_t>(); }
    inline void         Variable_t::Bool(const Bool_t value)        { Pack<Bool_t>(value); }
    inline Int_t        Variable_t::Int()                           { return Unpack<Int_t>(); }
    inline void         Variable_t::Int(const Int_t value)          { Pack<Int_t>(value); }
    inline Float_t      Variable_t::Float()                         { return Unpack<Float_t>(); }
    inline void         Variable_t::Float(const Float_t value)      { Pack<Float_t>(value); }
    inline String_t     Variable_t::String()                        { return Unpack<String_t>(); }
    inline void         Variable_t::String(const String_t value)    { Pack<String_t>(value); }
    template <typename Intrinsic_t>
    inline Intrinsic_t  Variable_t::As()                            { return Unpack<Intrinsic_t>(); }
    template <typename Intrinsic_t>
    inline void         Variable_t::As(const Intrinsic_t& value)    { Pack<Intrinsic_t>(value); }

    template <typename Intrinsic_t>
    inline Variable_t::operator Variable_tt<Intrinsic_t>*()
    {
        return reinterpret_cast<Variable_tt<Intrinsic_t>*>(this);
    }

    template <typename Intrinsic_t>
    inline          Variable_tt<Intrinsic_t>::operator Intrinsic_t()                { return Unpack<Intrinsic_t>(); }
    template <typename Intrinsic_t>
    inline void     Variable_tt<Intrinsic_t>::operator=(Intrinsic_t& value)         { Pack<Intrinsic_t>(value); }
    template <typename Intrinsic_t>
    inline void     Variable_tt<Intrinsic_t>::operator=(Intrinsic_t&& value)        { Pack<Intrinsic_t>(value); }
    template <typename Intrinsic_t>
    inline Bool_t   Variable_tt<Intrinsic_t>::operator==(const Intrinsic_t& value)  { return operator Intrinsic_t() == value; }
    template <typename Intrinsic_t>
    inline Bool_t   Variable_tt<Intrinsic_t>::operator==(Intrinsic_t&& value)       { return operator Intrinsic_t() == value; }
    template <typename Intrinsic_t>
    inline Bool_t   Variable_tt<Intrinsic_t>::operator!=(const Intrinsic_t& value)  { return !operator==(value); }
    template <typename Intrinsic_t>
    inline Bool_t   Variable_tt<Intrinsic_t>::operator!=(Intrinsic_t&& value)       { return !operator==(value); }

}}
