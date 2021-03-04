/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/collections.h"

#include "doticu_skylib/ni_3d.h"
#include "doticu_skylib/ni_node.h"

namespace doticu_skylib {

    Vector_t<some<NI_3D_t*>> NI_Node_t::Children()
    {
        Vector_t<some<NI_3D_t*>> results;
        Children(results);
        return results;
    }

    void NI_Node_t::Children(Vector_t<some<NI_3D_t*>>& results)
    {
        for (size_t idx = 0, end = this->children.count; idx < end; idx += 1) {
            maybe<NI_3D_t*> child = children.entries[idx];
            if (child) {
                results.push_back(child());
            }
        }
    }

}
