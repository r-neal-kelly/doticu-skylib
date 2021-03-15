/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe_numeric.h"

namespace doticu_skylib {

    using Raw_Container_Entry_Count_t = s32;

    class Container_Entry_Count_t
    {
    public:
        using value_type = Raw_Container_Entry_Count_t;

    protected:
        const value_type value;

    public:
        Container_Entry_Count_t();
        Container_Entry_Count_t(value_type value);

    public:
        operator value_type() const;
    };

}
