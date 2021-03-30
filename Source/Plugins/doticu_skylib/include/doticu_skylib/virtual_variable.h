/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/string.h"
#include "doticu_skylib/traits.h"

#include "doticu_skylib/enum_script_type.h"

#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_type.h"

namespace doticu_skylib { namespace Virtual {

    class Array_t;

    template <typename Intrinsic_t>
    class Variable_tt;

    union Variable_u
    {
    public:
        void*       ptr;
        Bool_t      b;
        Int_t       i;
        Float_t     f;
        String_t    str;
        Object_t*   obj;
        Array_t*    arr;

    public:
        Variable_u();
        Variable_u(const Variable_u& other);
        Variable_u(Variable_u&& other) noexcept;
        Variable_u& operator =(const Variable_u& other);
        Variable_u& operator =(Variable_u&& other) noexcept;
        ~Variable_u();
    };

    class Variable_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                COPY    = 0x01236E50, // 97509
                DESTROY = 0x01236D10, // 97508
            };
            using Enum_t::Enum_t;
        };

    public:
        Type_e      type;
        Variable_u  data;

        Variable_t();
        Variable_t(const Variable_t& other);
        Variable_t& operator=(const Variable_t& other);
        ~Variable_t();

        void Destroy();
        void Copy(const Variable_t& other);

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

    public:
        Object_t*               Object();
        Array_t*                Array();
        maybe<Script_Type_e>    Script_Type();

    public:
        template <typename Boolable_t, enable_if_virtual_bool_t<Boolable_t> = true>
        Boolable_t      Unpack();
        template <typename Intable_t, enable_if_virtual_int_t<Intable_t> = true>
        Intable_t       Unpack();
        template <typename Floatable_t, enable_if_virtual_float_t<Floatable_t> = true>
        Floatable_t     Unpack();
        template <typename Stringable_t, enable_if_virtual_string_t<Stringable_t> = true>
        Stringable_t    Unpack();
        template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t> = true>
        Scriptable_t    Unpack();
        template <typename Scriptable_t, enable_if_maybe_virtual_script_t<Scriptable_t> = true>
        Scriptable_t    Unpack();
        template <typename Scriptable_t, enable_if_some_virtual_script_t<Scriptable_t> = true>
        Scriptable_t    Unpack();
        template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t> = true>
        Arrayable_t     Unpack();

        template <typename Boolable_t, enable_if_virtual_bool_t<Boolable_t> = true>
        void            Unpack(Boolable_t& result);
        template <typename Intable_t, enable_if_virtual_int_t<Intable_t> = true>
        void            Unpack(Intable_t& result);
        template <typename Floatable_t, enable_if_virtual_float_t<Floatable_t> = true>
        void            Unpack(Floatable_t& result);
        template <typename Stringable_t, enable_if_virtual_string_t<Stringable_t> = true>
        void            Unpack(Stringable_t& result);
        template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t> = true>
        void            Unpack(Scriptable_t& result);
        template <typename Scriptable_t, enable_if_maybe_virtual_script_t<Scriptable_t> = true>
        void            Unpack(Scriptable_t& result);
        template <typename Scriptable_t, enable_if_some_virtual_script_t<Scriptable_t> = true>
        void            Unpack(Scriptable_t& result);
        template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t> = true>
        void            Unpack(Arrayable_t& results);

        template <typename Voidable_t, enable_if_void_t<Voidable_t> = true>
        void            Pack();
        template <typename Boolable_t, enable_if_virtual_bool_t<Boolable_t> = true>
        void            Pack(const Boolable_t& value);
        template <typename Intable_t, enable_if_virtual_int_t<Intable_t> = true>
        void            Pack(const Intable_t& value);
        template <typename Floatable_t, enable_if_virtual_float_t<Floatable_t> = true>
        void            Pack(const Floatable_t& value);
        template <typename Stringable_t, enable_if_virtual_string_t<Stringable_t> = true>
        void            Pack(const Stringable_t& value);
        template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t> = true>
        void            Pack(const Scriptable_t& value);
        template <typename Scriptable_t, enable_if_maybe_virtual_script_t<Scriptable_t> = true>
        void            Pack(const Scriptable_t& value);
        template <typename Scriptable_t, enable_if_some_virtual_script_t<Scriptable_t> = true>
        void            Pack(const Scriptable_t& value);
        template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t> = true>
        void            Pack(const Arrayable_t& values);

        template <typename Boolable_t, enable_if_virtual_bool_t<Boolable_t> = true>
        void            Pack(Boolable_t&& value);
        template <typename Intable_t, enable_if_virtual_int_t<Intable_t> = true>
        void            Pack(Intable_t&& value);
        template <typename Floatable_t, enable_if_virtual_float_t<Floatable_t> = true>
        void            Pack(Floatable_t&& value);
        template <typename Stringable_t, enable_if_virtual_string_t<Stringable_t> = true>
        void            Pack(Stringable_t&& value);
        template <typename Scriptable_t, enable_if_virtual_script_t<Scriptable_t> = true>
        void            Pack(Scriptable_t&& value);
        template <typename Scriptable_t, enable_if_maybe_virtual_script_t<Scriptable_t> = true>
        void            Pack(Scriptable_t&& value);
        template <typename Scriptable_t, enable_if_some_virtual_script_t<Scriptable_t> = true>
        void            Pack(Scriptable_t&& value);
        template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t> = true>
        void            Pack(Arrayable_t&& values);

    public:
        Bool_t      Bool();
        void        Bool(const Bool_t value);
        Int_t       Int();
        void        Int(const Int_t value);
        Float_t     Float();
        void        Float(const Float_t value);
        String_t    String();
        void        String(const String_t value);
        template <typename Intrinsic_t>
        Intrinsic_t As();
        template <typename Intrinsic_t>
        void        As(const Intrinsic_t& value);

        template <typename Intrinsic_t>
        operator Variable_tt<Intrinsic_t>*();
    };
    STATIC_ASSERT(sizeof(Variable_t) == 0x10);

    template <typename Intrinsic_t>
    class Variable_tt : public Variable_t
    {
    public:
        operator Intrinsic_t();

        void operator=(Intrinsic_t& value);
        void operator=(Intrinsic_t&& value);

        Bool_t operator==(const Intrinsic_t& value);
        Bool_t operator==(Intrinsic_t&& value);
        Bool_t operator!=(const Intrinsic_t& value);
        Bool_t operator!=(Intrinsic_t&& value);
    };
    STATIC_ASSERT(sizeof(Variable_tt<Int_t>) == sizeof(Variable_t));

}}
