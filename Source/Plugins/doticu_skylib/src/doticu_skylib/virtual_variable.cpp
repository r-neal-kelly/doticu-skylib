/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/form_type.h"
#include "doticu_skylib/game.h"

#include "doticu_skylib/virtual_object.h"
#include "doticu_skylib/virtual_policy.h"
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
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::DESTROY));
        destroy(this);
        data.ptr = nullptr;
    }

    void Variable_t::Copy(Variable_t* other)
    {
        static auto copy = reinterpret_cast
            <void (*)(Variable_t*, Variable_t*)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::COPY));
        Destroy();
        copy(this, other);
    }

    Bool_t Variable_t::Is_None()            { return type.Is_None(); }
    Bool_t Variable_t::Is_Bool()            { return type.Is_Bool(); }
    Bool_t Variable_t::Is_Int()             { return type.Is_Int(); }
    Bool_t Variable_t::Is_Float()           { return type.Is_Float(); }
    Bool_t Variable_t::Is_String()          { return type.Is_String(); }
    Bool_t Variable_t::Is_Object()          { return type.Is_Object(); }
    Bool_t Variable_t::Is_Array()           { return type.Is_Array(); }
    Bool_t Variable_t::Is_None_Array()      { return type.Is_None_Array(); }
    Bool_t Variable_t::Is_Object_Array()    { return type.Is_Object_Array(); }
    Bool_t Variable_t::Is_String_Array()    { return type.Is_String_Array(); }
    Bool_t Variable_t::Is_Int_Array()       { return type.Is_Int_Array(); }
    Bool_t Variable_t::Is_Float_Array()     { return type.Is_Float_Array(); }
    Bool_t Variable_t::Is_Bool_Array()      { return type.Is_Bool_Array(); }

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

    Reference_t* Variable_t::Reference()
    {
        if (type.Is_Object()) {
            if (data.obj) {
                return static_cast<Reference_t*>
                    (Handle_Policy_t::Self()->Resolve(Form_Type_e::REFERENCE, data.obj->Handle()));
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    Quest_t* Variable_t::Quest()
    {
        if (type.Is_Object()) {
            if (data.obj) {
                return static_cast<Quest_t*>
                    (Handle_Policy_t::Self()->Resolve(Form_Type_e::QUEST, data.obj->Handle()));
            } else {
                return nullptr;
            }
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

    Bool_t      Bool_Variable_t::Value()                    { return Bool(); }
    void        Bool_Variable_t::Value(Bool_t value)        { Bool(value); }

    Int_t       Int_Variable_t::Value()                     { return Int(); }
    void        Int_Variable_t::Value(Int_t value)          { Int(value); }

    Float_t     Float_Variable_t::Value()                   { return Float(); }
    void        Float_Variable_t::Value(Float_t value)      { Float(value); }

    String_t    String_Variable_t::Value()                  { return String(); }
    void        String_Variable_t::Value(String_t value)    { String(value); }

}}
