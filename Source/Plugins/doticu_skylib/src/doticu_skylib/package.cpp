/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/package.h"

namespace doticu_skylib {

    Bool_t Package_t::Is_Flagged(Package_Flags_e flag)
    {
        return (flags & flag) != 0;
    }

    Bool_t Package_t::Is_Flagged(Package_Interrupts_e flag)
    {
        return (flags & flag) != 0;
    }

    void Package_t::Flag(Package_Flags_e flag, Bool_t value)
    {
        if (value) {
            flags |= flag;
        } else {
            flags &= ~flag;
        }
    }

    void Package_t::Flag(Package_Interrupts_e flag, Bool_t value)
    {
        if (value) {
            interrupt_flags |= flag;
        } else {
            interrupt_flags &= ~flag;
        }
    }

}
