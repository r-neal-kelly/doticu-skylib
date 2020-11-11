/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib { namespace Virtual {

    Bool_t Variable_t::Bool()
    {
        if (type.Is_Bool()) {
            return data.b;
        } else {
            return false;
        }
    }

}}
