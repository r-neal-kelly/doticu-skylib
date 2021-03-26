/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_iterator.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    template <typename Return_t, typename ...Arguments>
    class Functor_i
    {
    public:
        virtual             ~Functor_i()                = default;
        virtual Return_t    operator()(Arguments...)    = 0;
    };

    template <typename ...Arguments>
    class Callback_i :
        public Functor_i<void, Arguments...>
    {
    public:
        static void*    operator new(size_t byte_count);
        static void     operator delete(void* data);

    public:
        virtual ~Callback_i() = default;
    };

    template <typename ...Arguments>
    class Iterator_i :
        public Functor_i<Iterator_e, Arguments...>
    {
    public:
        virtual ~Iterator_i() = default;
    };

    template <typename ...Arguments>
    class Filter_i :
        public Functor_i<Bool_t, Arguments...>
    {
    public:
        virtual ~Filter_i() = default;
    };

}
