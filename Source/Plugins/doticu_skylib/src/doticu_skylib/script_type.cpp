/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/script_type.h"

#include "doticu_skylib/virtual_class.h"

namespace doticu_skylib {

    maybe<Virtual::Class_t*> Script_Type_e::Class()
    {
        return Virtual::Class_t::Find_Or_Load(*this, true);
    }

}
