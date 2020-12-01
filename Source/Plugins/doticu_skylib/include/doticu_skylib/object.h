/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form.h"

namespace doticu_skylib {

    class Object_t : public Form_t
    {
    public:
        virtual ~Object_t();
    };
    STATIC_ASSERT(sizeof(Object_t) == 0x20);

}
