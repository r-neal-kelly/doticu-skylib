/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/virtual.h"

namespace doticu_skylib { namespace Virtual {

    class Class_t;

    enum class Type_e : u64 {
        NONE = 0,
        OBJECT = 1,
        STRING = 2,
        INT = 3,
        FLOAT = 4,
        BOOL = 5,

        NONE_ARRAY = 10,
        OBJECT_ARRAY = 11,
        STRING_ARRAY = 12,
        INT_ARRAY = 13,
        FLOAT_ARRAY = 14,
        BOOL_ARRAY = 15
    };

    class Type_t {
    public:
        u64 mangled;

        Type_t();
        Type_t(Type_e type);
        Type_t(Class_t* class_info);

        Type_e Unmangled();
        Class_t* Class_Info();
        String_t To_String();

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
    };
    STATIC_ASSERT(sizeof(Type_t) == 0x8);

}}
