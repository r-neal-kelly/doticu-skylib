/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Package_Target_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            SPECIFIC    = 0, // Reference_handle_t
            FORM_ID     = 1, // form_id. need to verify this isn't 5 instead.
            FORM_TYPE   = 2, // form_type
            LINKED      = 3, // Form_t*
            ALIAS_ID    = 4, // alias_id
            UNKNOWN     = 5, // unknown, interrupt flag?
            SELF        = 6, // nullptr
        };
        using Enum_t::Enum_t;
    };

}
