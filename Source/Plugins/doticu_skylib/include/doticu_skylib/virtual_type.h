/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/enum_script_type.h"

#include "doticu_skylib/virtual.h"

namespace doticu_skylib { namespace Virtual {

    class Class_t;

    using Raw_Type_t = u64;

    class Type_e
    {
    public:
        enum : Raw_Type_t
        {
            NONE            = 0,
            OBJECT          = 1,
            STRING          = 2,
            INT             = 3,
            FLOAT           = 4,
            BOOL            = 5,

            NONE_ARRAY      = 10,
            OBJECT_ARRAY    = 11,
            STRING_ARRAY    = 12,
            INT_ARRAY       = 13,
            FLOAT_ARRAY     = 14,
            BOOL_ARRAY      = 15,
        };

        template <typename Voidable_t = void, enable_if_void_t<Voidable_t> = true>
        static Type_e From();
        template <typename Boolable_t, enable_if_virtual_bool_t<Boolable_t> = true>
        static Type_e From();
        template <typename Intable_t, enable_if_virtual_int_t<Intable_t> = true>
        static Type_e From();
        template <typename Floatable_t, enable_if_virtual_float_t<Floatable_t> = true>
        static Type_e From();
        template <typename Stringable_t, enable_if_virtual_string_t<Stringable_t> = true>
        static Type_e From();
        template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t> = true>
        static Type_e From();
        template <typename Scriptable_t, enable_if_wrapped_virtual_script_t<Scriptable_t> = true>
        static Type_e From();
        template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t> = true>
        static Type_e From();

    public:
        // mangled can be any of the above enums,
        // a reinterpret_cast<Raw_Type_t>(Class_t*) to indicate an object of said class,
        // or a reinterpret_cast<Raw_Type_t>(Class_t*) | 1llu to indicate an array of the class's objects
        Raw_Type_t mangled;

    public:
        Type_e();
        Type_e(Raw_Type_t raw_type);
        Type_e(maybe<Class_t*> vclass);
        Type_e(Script_Type_e script_type);

        Type_e(const Type_e& other);
        Type_e(Type_e&& other) noexcept;
        Type_e& operator=(const Type_e& other);
        Type_e& operator=(Type_e&& other) noexcept;

        ~Type_e();

    public:
        Bool_t operator==(const Type_e& other);
        Bool_t operator==(const Type_e& other) const;

    public:
        Raw_Type_t  Mangled() const;
        Raw_Type_t  Unmangled() const;
        Class_t*    Class();
        String_t    To_String();
        Type_e      As_Array();

    public:
        Bool_t  Is_None();
        Bool_t  Is_Bool();
        Bool_t  Is_Int();
        Bool_t  Is_Float();
        Bool_t  Is_String();
        Bool_t  Is_Object();
        Bool_t  Is_Array();
        Bool_t  Is_None_Array();
        Bool_t  Is_Bool_Array();
        Bool_t  Is_Int_Array();
        Bool_t  Is_Float_Array();
        Bool_t  Is_String_Array();
        Bool_t  Is_Object_Array();
    };
    STATIC_ASSERT(sizeof(Type_e) == 0x8);

}}

namespace doticu_skylib { namespace Virtual {

    template <typename Voidable_t, enable_if_void_t<Voidable_t>>
    inline Type_e Type_e::From()
    {
        return Type_e::NONE;
    }

    template <typename Boolable_t, enable_if_virtual_bool_t<Boolable_t>>
    inline Type_e Type_e::From()
    {
        return Type_e::BOOL;
    }

    template <typename Intable_t, enable_if_virtual_int_t<Intable_t>>
    inline Type_e Type_e::From()
    {
        return Type_e::INT;
    }

    template <typename Floatable_t, enable_if_virtual_float_t<Floatable_t>>
    inline Type_e Type_e::From()
    {
        return Type_e::FLOAT;
    }

    template <typename Stringable_t, enable_if_virtual_string_t<Stringable_t>>
    inline Type_e Type_e::From()
    {
        return Type_e::STRING;
    }

    template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t>>
    inline Type_e Type_e::From()
    {
        return Script_Type_e::From<Scriptable_t>()();
    }

    template <typename Scriptable_t, enable_if_wrapped_virtual_script_t<Scriptable_t>>
    inline Type_e Type_e::From()
    {
        return Script_Type_e::From<typename Scriptable_t::value_type>()();
    }

    template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t>>
    inline Type_e Type_e::From()
    {
        return From<Arrayable_t::value_type>().As_Array();
    }

}}
