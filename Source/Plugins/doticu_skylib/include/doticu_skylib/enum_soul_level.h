/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Soul_Level_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_  = static_cast<value_type>(-1),

            EMPTY   = static_cast<value_type>(0),
            PETTY   = static_cast<value_type>(1),
            LESSER  = static_cast<value_type>(2),
            COMMON  = static_cast<value_type>(3),
            GREATER = static_cast<value_type>(4),
            GRAND   = static_cast<value_type>(5),

            _TOTAL_ = static_cast<value_type>(6),
        };

    public:
        static some<const char* const*> Strings();
        static some<const char*>        To_String(Soul_Level_e soul_level);
        static Soul_Level_e             From_String(maybe<const char*> soul_level);

    public:
        using Enum_t::Enum_t;

    public:
        some<const char*> As_String();

    public:
        explicit operator Bool_t() const;
    };

}
