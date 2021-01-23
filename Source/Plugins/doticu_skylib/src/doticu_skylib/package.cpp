/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/package.h"

namespace doticu_skylib {

    Bool_t Package_t::Is_Flagged(Package_Flags_e flag)
    {
        return (this->package_flags & flag) != 0;
    }

    Bool_t Package_t::Is_Flagged(Package_Interrupts_e flag)
    {
        return (this->interrupt_flags & flag) != 0;
    }

    void Package_t::Flag(Package_Flags_e flag, Bool_t value)
    {
        if (value) {
            this->package_flags |= flag;
        } else {
            this->package_flags &= ~flag;
        }
    }

    void Package_t::Flag(Package_Interrupts_e flag, Bool_t value)
    {
        if (value) {
            this->interrupt_flags |= flag;
        } else {
            this->interrupt_flags &= ~flag;
        }
    }

}
