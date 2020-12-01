/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/location.h"

namespace doticu_skylib {

    String_t Location_t::Any_Name()
    {
        const char* name = Name();
        if (!name || !name[0]) {
            name = Get_Editor_ID();
            if (!name || !name[0]) {
                return Form_ID_String();
            } else {
                return name;
            }
        } else {
            return name;
        }
    }

}
