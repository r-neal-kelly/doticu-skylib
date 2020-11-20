/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "common/IErrors.h"

#include "doticu_skylib/intrinsic.h"

#define M \
    do {

#define W \
    } while (0)

#if 1

#define SKYLIB_ASSERT(IS_TRUE_)                                         \
M                                                                       \
    if (!(IS_TRUE_)) {                                                  \
        _MESSAGE("Asserted. Exiting Skyrim. Failed: %s", #IS_TRUE_);    \
        _AssertionFailed(__FILE__, __LINE__, #IS_TRUE_);                \
    }                                                                   \
W

#else

#define SKYLIB_ASSERT(IGNORED_)

#endif

namespace doticu_skylib {

    constexpr Float_t PI = 3.141592741f;

    template <typename Num>
    inline Bool_t Is_Odd(Num num)
    {
        return num & static_cast<Num>(1);
    }

    template <typename Num>
    inline Bool_t Is_Even(Num num)
    {
        return !Is_Odd(num);
    }

    class CString_t {
    public:
        static constexpr Word_t MAX_LENGTH = 2048;

        static Word_t Length(const char* sub);

        static Bool_t Is_Same(const char* sub, const char* obj, Bool_t caseless);
        static Bool_t Starts_With(const char* sub, const char* obj, Bool_t caseless);
        static Bool_t Starts_With(const char* sub, const char obj, Bool_t caseless);
        static Bool_t Ends_With(const char* sub, const char* obj, Bool_t caseless);
        static Bool_t Ends_With(const char* sub, const char obj, Bool_t caseless);
        static Bool_t Contains(const char* sub, const char* obj, Bool_t caseless);
    };

    inline Word_t V_Table_Offset(void* instance)
    {
        return *reinterpret_cast<uintptr_t*>(instance) - RelocationManager::s_baseAddr;
    }

    inline void Add_V_Table(void* instance, Word_t v_table_offset)
    {
        static_cast<Word_t*>(instance)[0] = RelocationManager::s_baseAddr + v_table_offset;
    }

}
