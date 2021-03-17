/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_class.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_type.h"

namespace doticu_skylib { namespace Virtual {

    Type_e::Type_e()
    {
        mangled = Type_e::NONE;
    }

    Type_e::Type_e(Raw_Type_t raw_type)
    {
        if (raw_type == Type_e::OBJECT) {
            mangled = Type_e::NONE;
        } else if (raw_type == Type_e::OBJECT_ARRAY) {
            mangled = Type_e::NONE_ARRAY;
        } else {
            mangled = raw_type;
        }
    }

    Type_e::Type_e(maybe<Class_t*> vclass)
    {
        if (vclass) {
            mangled = reinterpret_cast<Raw_Type_t>(vclass());
        } else {
            mangled = Type_e::NONE;
        }
    }

    Type_e::Type_e(Script_Type_e script_type)
    {
        mangled = Type_e(script_type.Class()).mangled;
    }

    Type_e::Type_e(const Type_e& other)
    {
        mangled = other.mangled;
    }

    Type_e::Type_e(Type_e&& other) noexcept
    {
        if (other.Is_Array()) {
            mangled = std::exchange(other.mangled, Type_e::NONE_ARRAY);
        } else {
            mangled = std::exchange(other.mangled, Type_e::NONE);
        }
    }

    Type_e& Type_e::operator=(const Type_e& other)
    {
        if (this != &other) {
            mangled = other.mangled;
        }
        return *this;
    }

    Type_e& Type_e::operator=(Type_e&& other) noexcept
    {
        if (this != &other) {
            if (other.Is_Array()) {
                mangled = std::exchange(other.mangled, Type_e::NONE_ARRAY);
            } else {
                mangled = std::exchange(other.mangled, Type_e::NONE);
            }
        }
        return *this;
    }

    Type_e::~Type_e()
    {
        mangled = Type_e::NONE;
    }

    Bool_t Type_e::operator==(const Type_e& other)
    {
        return mangled == other.mangled;
    }

    Bool_t Type_e::operator==(const Type_e& other) const
    {
        return mangled == other.mangled;
    }

    Raw_Type_t Type_e::Mangled() const
    {
        return mangled;
    }

    Raw_Type_t Type_e::Unmangled() const
    {
        if (mangled <= Type_e::BOOL_ARRAY) {
            return mangled;
        } else {
            if ((mangled & 1llu) > 0) {
                return Type_e::OBJECT_ARRAY;
            } else {
                return Type_e::OBJECT;
            }
        }
    }

    Class_t* Type_e::Class()
    {
        if (Is_Object()) {
            return reinterpret_cast<Class_t*>(mangled);
        } else if (Is_Object_Array()) {
            return reinterpret_cast<Class_t*>(mangled & ~1llu);
        } else {
            return nullptr;
        }
    }

    String_t Type_e::To_String()
    {
        switch (Unmangled()) {
            case Type_e::NONE:          return "None";
            case Type_e::OBJECT:        return Class()->name;
            case Type_e::STRING:        return "String";
            case Type_e::INT:           return "Int";
            case Type_e::FLOAT:         return "Float";
            case Type_e::BOOL:          return "Bool";
            case Type_e::NONE_ARRAY:    return "None[]";
            case Type_e::OBJECT_ARRAY:  return Class()->name + "[]";
            case Type_e::STRING_ARRAY:  return "String[]";
            case Type_e::INT_ARRAY:     return "Int[]";
            case Type_e::FLOAT_ARRAY:   return "Float[]";
            case Type_e::BOOL_ARRAY:    return "Bool[]";
            default:                    return "Invalid";
        };
    }

    Type_e Type_e::As_Array()
    {
        Type_e type;
        if (mangled < Type_e::NONE_ARRAY) {
            type.mangled = mangled + Type_e::NONE_ARRAY;
        } else if (mangled > Type_e::BOOL_ARRAY) {
            type.mangled = mangled | 1llu;
        } else {
            type.mangled = mangled;
        }
        return type;
    }

    Bool_t Type_e::Is_None()
    {
        return Unmangled() == Type_e::NONE;
    }

    Bool_t Type_e::Is_Bool()
    {
        return Unmangled() == Type_e::BOOL;
    }

    Bool_t Type_e::Is_Int()
    {
        return Unmangled() == Type_e::INT;
    }

    Bool_t Type_e::Is_Float()
    {
        return Unmangled() == Type_e::FLOAT;
    }

    Bool_t Type_e::Is_String()
    {
        return Unmangled() == Type_e::STRING;
    }

    Bool_t Type_e::Is_Object()
    {
        return Unmangled() == Type_e::OBJECT;
    }

    Bool_t Type_e::Is_Array()
    {
        Raw_Type_t unmangled = Unmangled();
        return unmangled >= Type_e::NONE_ARRAY && unmangled <= Type_e::BOOL_ARRAY;
    }

    Bool_t Type_e::Is_None_Array()
    {
        return Unmangled() == Type_e::NONE_ARRAY;
    }

    Bool_t Type_e::Is_Bool_Array()
    {
        return Unmangled() == Type_e::BOOL_ARRAY;
    }

    Bool_t Type_e::Is_Int_Array()
    {
        return Unmangled() == Type_e::INT_ARRAY;
    }

    Bool_t Type_e::Is_Float_Array()
    {
        return Unmangled() == Type_e::FLOAT_ARRAY;
    }

    Bool_t Type_e::Is_String_Array()
    {
        return Unmangled() == Type_e::STRING_ARRAY;
    }

    Bool_t Type_e::Is_Object_Array()
    {
        return Unmangled() == Type_e::OBJECT_ARRAY;
    }

}}
