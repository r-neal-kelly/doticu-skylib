/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class CString_t
    {
    public:
        static constexpr Word_t MAX_LENGTH = 2048;

        static Word_t Length(const char* sub, Bool_t with_null = false);

        static Bool_t Is_Same(const char* sub, const char* obj, Bool_t caseless);
        static Bool_t Starts_With(const char* sub, const char* obj, Bool_t caseless);
        static Bool_t Starts_With(const char* sub, const char obj, Bool_t caseless);
        static Bool_t Ends_With(const char* sub, const char* obj, Bool_t caseless);
        static Bool_t Ends_With(const char* sub, const char obj, Bool_t caseless);
        static Bool_t Contains(const char* sub, const char* obj, Bool_t caseless);

        static Bool_t Is_Length_Less_Than(const char* sub, Word_t length, Bool_t with_null = false);
        static Bool_t Is_Length_Greater_Than(const char* sub, Word_t length, Bool_t with_null = false);
    };

}