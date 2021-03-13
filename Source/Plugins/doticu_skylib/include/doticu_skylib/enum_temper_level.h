/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Temper_Level_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_      = static_cast<value_type>(-1),

            STANDARD    = static_cast<value_type>(0),
            FINE        = static_cast<value_type>(1),
            SUPERIOR    = static_cast<value_type>(2),
            EXQUISITE   = static_cast<value_type>(3),
            FLAWLESS    = static_cast<value_type>(4),
            EPIC        = static_cast<value_type>(5),
            LEGENDARY   = static_cast<value_type>(6),

            _TOTAL_     = static_cast<value_type>(7),
        };

    public:
        static some<const Float_t*>     Floats();
        static Float_t                  To_Float(Temper_Level_e temper_level);
        static Temper_Level_e           From_Float(Float_t temper_level);

        static some<const char* const*> Strings();
        static some<const char*>        To_String(Temper_Level_e temper_level);
        static Temper_Level_e           From_String(maybe<const char*> temper_level);

    public:
        using Enum_t::Enum_t;

    public:
        Float_t             As_Float();
        some<const char*>   As_String();

    public:
        explicit operator Bool_t() const;
    };

}
