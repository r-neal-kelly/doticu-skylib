/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ni_extras.h"

namespace doticu_skylib {

    Vector_t<some<NI_Extra_t*>> NI_Extras_t::Extras()
    {
        Vector_t<some<NI_Extra_t*>> results;
        Extras(results);
        return results;
    }

    void NI_Extras_t::Extras(Vector_t<some<NI_Extra_t*>>& results)
    {
        for (size_t idx = 0, end = this->extra_count; idx < end; idx += 1) {
            maybe<NI_Extra_t*> extra = this->extras[idx];
            if (extra) {
                results.push_back(extra());
            }
        }
    }

}
