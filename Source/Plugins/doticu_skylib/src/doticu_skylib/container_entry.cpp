/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/container_entry.h"

namespace doticu_skylib {

    Container_Entry_Count_t Container_Entry_t::Count()
    {
        return this->count;
    }

    void Container_Entry_t::Count(Container_Entry_Count_t count)
    {
        this->count = count;
    }

}
