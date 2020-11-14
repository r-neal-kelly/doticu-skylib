/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib { namespace Virtual {

    Variable_u::Variable_u() :
        ptr(nullptr)
    {
    }

    Variable_t::Variable_t() :
        type(Type_t()), data(Variable_u())
    {
    }

    void Variable_t::Destroy()
    {
        static auto destroy = reinterpret_cast
            <void (*)(Variable_t*)>
            (RelocationManager::s_baseAddr + static_cast<Word_t>(Offset_t::DESTROY));
        destroy(this);
        data.ptr = nullptr;
    }

    void Variable_t::Copy(Variable_t* other)
    {
        static auto copy = reinterpret_cast
            <void (*)(Variable_t*, Variable_t*)>
            (RelocationManager::s_baseAddr + static_cast<Word_t>(Offset_t::COPY));
        Destroy();
        copy(this, other);
    }

    Bool_t Variable_t::Bool()
    {
        if (type.Is_Bool()) {
            return data.b;
        } else {
            return false;
        }
    }

    Int_t Variable_t::Int()
    {
        if (type.Is_Int()) {
            return data.i;
        } else {
            return 0;
        }
    }

    Float_t Variable_t::Float()
    {
        if (type.Is_Float()) {
            return data.f;
        } else {
            return 0.0;
        }
    }

    String_t Variable_t::String()
    {
        if (type.Is_String()) {
            return data.str;
        } else {
            return "";
        }
    }

    Object_t* Variable_t::Object()
    {
        if (type.Is_Object()) {
            return data.obj;
        } else {
            return nullptr;
        }
    }

    Array_t* Variable_t::Array()
    {
        if (type.Is_Array()) {
            return data.arr;
        } else {
            return nullptr;
        }
    }

    Array_t* Variable_t::Object_Array()
    {
        if (type.Is_Object_Array()) {
            return data.arr;
        } else {
            return nullptr;
        }
    }

    void Variable_t::None(Type_t type)
    {
        Destroy();
        this->type = type;
        this->data.ptr = nullptr;
    }

    void Variable_t::Bool(Bool_t value)
    {
        Destroy();
        type = Type_e::BOOL;
        data.b = value;
    }

    void Variable_t::Int(Int_t value)
    {
        Destroy();
        type = Type_e::INT;
        data.i = value;
    }

    void Variable_t::Float(Float_t value)
    {
        Destroy();
        type = Type_e::FLOAT;
        data.f = value;
    }

    void Variable_t::String(String_t value)
    {
        Destroy();
        type = Type_e::STRING;
        data.str.Value(value);
    }

    String_t String_Variable_t::Value()
    {
        return String();
    }

    void String_Variable_t::Value(String_t value)
    {
        String(value);
    }

    String_Variable_t::operator String_t()
    {
        return String();
    }

}}
