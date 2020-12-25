/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/form_type.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/reference.h"

#include "doticu_skylib/virtual_object.h"
#include "doticu_skylib/virtual_policy.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib { namespace Virtual {

    Variable_u::Variable_u() :
        ptr(nullptr)
    {
    }

    Variable_t::Variable_t() :
        type(Type_e()), data(Variable_u())
    {
    }

    Variable_t::Variable_t(const Variable_t& other)
    {
        if (this != &other) {
            Copy(other);
        }
    }

    Variable_t& Variable_t::operator=(const Variable_t& other)
    {
        if (this != &other) {
            Copy(other);
        }
        return *this;
    }

    Variable_t::~Variable_t()
    {
        Destroy();
    }

    void Variable_t::Destroy()
    {
        static auto destroy = reinterpret_cast
            <void (*)(Variable_t*)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::DESTROY));

        destroy(this);
        type = Type_e();
        data = Variable_u();
    }

    void Variable_t::Copy(const Variable_t& other)
    {
        static auto copy = reinterpret_cast
            <void (*)(const Variable_t*, const Variable_t&)>
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
    Bool_t Variable_t::Is_Bool_Array()      { return type.Is_Bool_Array(); }
    Bool_t Variable_t::Is_Int_Array()       { return type.Is_Int_Array(); }
    Bool_t Variable_t::Is_Float_Array()     { return type.Is_Float_Array(); }
    Bool_t Variable_t::Is_String_Array()    { return type.Is_String_Array(); }
    Bool_t Variable_t::Is_Object_Array()    { return type.Is_Object_Array(); }

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

    maybe<Script_Type_e> Variable_t::Script_Type()
    {
        Class_t* vclass = type.Class();
        if (vclass) {
            return vclass->Script_Type();
        } else {
            return none<Script_Type_e>();
        }
    }

    Bool_t      Bool_Variable_t::Value()                    { return Unpack<Bool_t>(); }
    void        Bool_Variable_t::Value(Bool_t value)        { Pack<Bool_t>(value); }

    Int_t       Int_Variable_t::Value()                     { return Unpack<Int_t>(); }
    void        Int_Variable_t::Value(Int_t value)          { Pack<Int_t>(value); }

    Float_t     Float_Variable_t::Value()                   { return Unpack<Float_t>(); }
    void        Float_Variable_t::Value(Float_t value)      { Pack<Float_t>(value); }

    String_t    String_Variable_t::Value()                  { return Unpack<String_t>(); }
    void        String_Variable_t::Value(String_t value)    { Pack<String_t>(value); }

}}
