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

        public:
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
        void    Write(maybe<const char*> value);

    public:
        explicit operator   Bool_t() const;
        operator            const char*() const;
        operator            maybe<const char*>() const;
        operator            some<const char*>() const;

    public:
        Bool_t  operator !() const;
        Bool_t  operator ==(const Static_String_t& other) const;
        Bool_t  operator !=(const Static_String_t& other) const;

    public:
        friend std::string operator +(const Static_String_t& a, const Static_String_t& b);
        friend std::string operator +(const Static_String_t& a, const char* b);
        friend std::string operator +(const char* a, const Static_String_t& b);
        friend std::string operator +(const Static_String_t& a, const std::string& b);
        friend std::string operator +(const std::string& a, const Static_String_t& b);

        friend Bool_t operator ==(const Static_String_t& a, const char* b);
        friend Bool_t operator ==(const char* a, const Static_String_t& b);
    };
    STATIC_ASSERT(sizeof(Static_String_t) == 0x8);

    using String_t = Static_String_t;

    class Dynamic_String_t
    {
    public:
        class Offset_e :
            Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                SET = 0x000F9E90, // 10979
            };
            using Enum_t::Enum_t;
        };

    public:
        maybe<char*>    value;      // 00
        u16             length;     // 08
        u16             capacity;   // 0A
        u32             pad_0C;     // 0C

    public:
        Dynamic_String_t();
        Dynamic_String_t(const char* string);
        Dynamic_String_t(const Dynamic_String_t& other);
        Dynamic_String_t(Dynamic_String_t&& other) noexcept;
        Dynamic_String_t& operator =(const Dynamic_String_t& other);
        Dynamic_String_t& operator =(Dynamic_String_t&& other) noexcept;
        ~Dynamic_String_t();

    public:
        void Write(maybe<const char*> string);
        void Clear();

    public:
        explicit operator   Bool_t() const;
        operator            const char*() const;
        operator            maybe<const char*>() const;
        operator            some<const char*>() const;

    public:
        Bool_t              operator !() const;
        some<const char*>   operator ()() const;
        Bool_t              operator ==(const Dynamic_String_t& other) const;
        Bool_t              operator !=(const Dynamic_String_t& other) const;

    public:
        friend std::string operator +(const Dynamic_String_t& a, const Dynamic_String_t& b);
        friend std::string operator +(const Dynamic_String_t& a, const char* b);
        friend std::string operator +(const char* a, const Dynamic_String_t& b);
        friend std::string operator +(const Dynamic_String_t& a, const std::string& b);
        friend std::string operator +(const std::string& a, const Dynamic_String_t& b);

        friend Bool_t operator ==(const Dynamic_String_t& a, const char* b);
        friend Bool_t operator ==(const char* a, const Dynamic_String_t& b);
    };
    STATIC_ASSERT(sizeof(Dynamic_String_t) == 0x10);

    using DString_t = Dynamic_String_t;

}
