/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_type.h"

namespace doticu_skylib { namespace Virtual {

    Type_t::Type_t() :
        mangled(static_cast<u64>(Type_e::NONE))
    {
    }

    Type_t::Type_t(Type_e type) :
        mangled(static_cast<u64>(type))
    {
    }

    Type_t::Type_t(Class_t* class_info) :
        mangled(reinterpret_cast<u64>(class_info))
    {
    }

    Type_e Type_t::Unmangled()
    {
        if (static_cast<Type_e>(mangled) <= Type_e::BOOL_ARRAY) {
            return static_cast<Type_e>(mangled);
        } else {
            return (mangled & 1llu) ? Type_e::OBJECT_ARRAY : Type_e::OBJECT;
        }
    }

    Bool_t Type_t::Is_None()
    {
        return Unmangled() == Type_e::NONE;
    }

    Bool_t Type_t::Is_Bool()
    {
        return Unmangled() == Type_e::BOOL;
    }

    Bool_t Type_t::Is_Int()
    {
        return Unmangled() == Type_e::INT;
    }

    Bool_t Type_t::Is_Float()
    {
        return Unmangled() == Type_e::FLOAT;
    }

    Bool_t Type_t::Is_String()
    {
        return Unmangled() == Type_e::STRING;
    }

    Bool_t Type_t::Is_Object()
    {
        return Unmangled() == Type_e::OBJECT;
    }

    Bool_t Type_t::Is_Array()
    {
        Type_e unmangled = Unmangled();
        return unmangled >= Type_e::NONE_ARRAY && unmangled <= Type_e::BOOL_ARRAY;
    }

    Bool_t Type_t::Is_None_Array()
    {
        return Unmangled() == Type_e::NONE_ARRAY;
    }

    Bool_t Type_t::Is_Bool_Array()
    {
        return Unmangled() == Type_e::BOOL_ARRAY;
    }

    Bool_t Type_t::Is_Int_Array()
    {
        return Unmangled() == Type_e::INT_ARRAY;
    }

    Bool_t Type_t::Is_Float_Array()
    {
        return Unmangled() == Type_e::FLOAT_ARRAY;
    }

    Bool_t Type_t::Is_String_Array()
    {
        return Unmangled() == Type_e::STRING_ARRAY;
    }

    Bool_t Type_t::Is_Object_Array()
    {
        return Unmangled() == Type_e::OBJECT_ARRAY;
    }

    Bool_t Type_t::operator ==(const Type_t& other)
    {
        return Unmangled() == const_cast<Type_t&>(other).Unmangled();
    }

    Bool_t Type_t::operator ==(const Type_e& type)
    {
        return Unmangled() == type;
    }

}}
