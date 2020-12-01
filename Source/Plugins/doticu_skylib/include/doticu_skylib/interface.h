/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    template <typename ...Arguments>
    class Functor_i
    {
    public:
        virtual ~Functor_i() = default;
        virtual void operator()(Arguments...) = 0;
    };

    template <typename ...Arguments>
    class Callback_i
    {
    public:
        virtual ~Callback_i() = default;
        virtual void operator()(Arguments...) = 0;
    };

    template <typename Return, typename ...Arguments>
    class Iterator_i
    {
    public:
        virtual ~Iterator_i() = default;
        virtual Return operator()(Arguments...) = 0;
    };

}
