/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/keyword.h"

namespace doticu_skylib {

    String_t Keyword_t::Any_Name()
    {
        const char* name = Get_Editor_ID();
        if (name && name[0]) {
            return name;
        } else {
            return Form_ID_String();
        }
    }

}
