/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/package.h"

namespace doticu_skylib {

    Bool_t Package_t::Is_Flagged(Package_Flags_e flag)
    {
        return this->package_flags.Is_Flagged(flag);
    }

    Bool_t Package_t::Is_Flagged(Package_Interrupts_e flag)
    {
        return this->interrupt_flags.Is_Flagged(flag);
    }

    void Package_t::Flag(Package_Flags_e flag, Bool_t value)
    {
        if (value) {
            this->package_flags.Flag(flag);
        } else {
            this->package_flags.Unflag(flag);
        }
    }

    void Package_t::Flag(Package_Interrupts_e flag, Bool_t value)
    {
        if (value) {
            this->interrupt_flags.Flag(flag);
        } else {
            this->interrupt_flags.Unflag(flag);
        }
    }

}
