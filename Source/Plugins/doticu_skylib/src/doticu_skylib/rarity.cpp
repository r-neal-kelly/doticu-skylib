/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/rarity.h"

namespace doticu_skylib {

    const char* Rarity_e::To_String(Rarity_e rarity_e)
    {
        switch (rarity_e) {
            case (Rarity_e::UNIQUE):    return "Unique";
            case (Rarity_e::GENERIC):   return "Generic";
            default:                    return "None";
        }
    }

}
