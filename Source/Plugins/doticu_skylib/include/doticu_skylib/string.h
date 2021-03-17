/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Static_String_t
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                CREATE  = 0x00C28BF0, // 67819
                DESTROY = 0x00C28D40, // 67822
                SET     = 0x00C28D60, // 67823
            };
            using Enum_t::Enum_t;
        };

    protected:
        maybe<const char*> value;

    public:
        Static_String_t();
        Static_String_t(const char* string);
        Static_String_t(maybe<const char*> string);
        Static_String_t(some<const char*> string);
        Static_String_t(std::string& string);
        Static_String_t(std::string&& string) noexcept;
        Static_String_t(const Static_String_t& other);
        Static_String_t(Static_String_t&& other) noexcept;
        Static_String_t& operator =(const Static_String_t& other);
        Static_String_t& operator =(Static_String_t&& other) noexcept;
        ~Static_String_t();

    public:
        void    Destroy();
        void    Write(const char* value);

    public:
        explicit operator   Bool_t() const;
        operator            const char*() const;
        operator            some<const char*>() const;
        operator            std::string() const;

    public:
        Bool_t  operator !() const;
        Bool_t  operator ==(const Static_String_t& other) const;
        Bool_t  operator !=(const Static_String_t& other) const;

        friend std::string operator +(const std::string& a, const Static_String_t& b);
    };
    STATIC_ASSERT(sizeof(Static_String_t) == 0x8);

    class Dynamic_String_t
    {
    public:
        class Offset_e : Enum_t<Word_t>
        {
        public:
            enum
            {
                SET = 0x000F9E90,
            };
            using Enum_t::Enum_t;
        };

    public:
        char*   data;       // 0
        u16     length;     // 8
        u16     capacity;   // A
        u32     pad_0C;     // C

    public:
        Dynamic_String_t();
        Dynamic_String_t(const char* other);
        Dynamic_String_t(Dynamic_String_t&& other) noexcept;
        Dynamic_String_t& operator=(const char* other);
        ~Dynamic_String_t();

    public:
        Bool_t operator==(const char* other) const;
        Bool_t operator!=(const char* other) const;

    public:
        explicit operator Bool_t() const;
        Bool_t operator !() const;
        operator const char*() const;
    };
    STATIC_ASSERT(sizeof(Dynamic_String_t) == 0x10);

    using String_t = Static_String_t;
    using DString_t = Dynamic_String_t;

}
