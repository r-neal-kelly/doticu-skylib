/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    using Raw_Remove_Reason_t = u32;

    class Remove_Reason_e :
        public Enum_t<Raw_Remove_Reason_t>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_      = static_cast<value_type>(-1),

            DEFAULT     = static_cast<value_type>(0),
            STEAL       = static_cast<value_type>(1),
            SELL        = static_cast<value_type>(2),
            DROP        = static_cast<value_type>(3),
            CONTAINER   = static_cast<value_type>(4),
            TEAMMATE    = static_cast<value_type>(5),

            _TOTAL_     = static_cast<value_type>(6),
        };

    public:
        static some<const char* const*> Strings();
        static some<const char*>        To_String(Remove_Reason_e remove_reason);
        static Remove_Reason_e          From_String(maybe<const char*> remove_reason);

    public:
        using Enum_t::Enum_t;

    public:
        some<const char*> As_String();

    public:
        explicit operator Bool_t() const;
    };

}
