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

    Bool_t Type_t::Is_Bool()
    {
        return Unmangled() == Type_e::BOOL;
    }

}}
