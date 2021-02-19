/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/enum_sex.h"

namespace doticu_skylib {

    const char* Sex_e::To_String(Sex_e sex_e)
    {
        switch (sex_e) {
            case (Sex_e::MALE):     return "Male";
            case (Sex_e::FEMALE):   return "Female";
            default:                return "None";
        }
    }

}
