/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/component_name.h"

namespace doticu_skylib {

    String_t Name_c::Name()
    {
        return this->name;
    }

    void Name_c::Name(String_t name)
    {
        this->name = name;
    }

}
