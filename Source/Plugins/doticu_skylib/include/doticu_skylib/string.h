/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Static_String_t
    {
    public:
        class Offset_e : Enum_t<Word_t>
        {
        public:
            enum
            {
                CREATE  = 0x00C28BF0, // 67819
                DESTROY = 0x00C28D40, // 67822
                SET     = 0x00C28D60, // 67823
            };
            using Enum_t::Enum_t;
        };

    public:
        const char* data;

        Static_String_t();
        Static_String_t(const char* string);
        Static_String_t(std::string& string);
        Static_String_t(std::string&& string);

        void        Destroy();

        const char* Value();
        void        Value(const char* value);

        Bool_t      operator==(const Static_String_t& other);
        Bool_t      operator==(const Static_String_t& other) const;
        Bool_t      operator!=(const Static_String_t& other);
        Bool_t      operator!=(const Static_String_t& other) const;

        explicit operator Bool_t();
        explicit operator Bool_t() const;
        operator const char*();
    };
    STATIC_ASSERT(sizeof(Static_String_t) == 0x8);

    class Dynamic_String_t
    {
    public:
        char*   data;       // 0
        u16     length;     // 8
        u16     capacity;   // A
        u32     pad_0C;     // C
    };
    STATIC_ASSERT(sizeof(Dynamic_String_t) == 0x10);

    using String_t = Static_String_t;

}
