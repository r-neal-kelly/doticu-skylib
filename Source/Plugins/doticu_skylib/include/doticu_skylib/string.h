/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class String_t : public BSFixedString {
    public:
        class Offset_e : Enum_t<Word_t> {
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
        String_t();
        String_t(const char* string);
        String_t(std::string&& string);

        void Destroy();

        const char* Value();
        void Value(const char* value);

        Bool_t operator==(const String_t& other);
        Bool_t operator!=(const String_t& other);
        Bool_t operator!();
        operator Bool_t();
    };

}
