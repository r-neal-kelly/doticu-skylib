/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/forward_list.h"

namespace doticu_skylib {

    template <typename Type_t>
    inline Bool_t Forward_List_t<Type_t>::Is_Empty()
    {
        return !head.value;
    }

    template <typename Type_t>
    inline maybe<Type_t*> Forward_List_t<Type_t>::Point(some<Index_t> index)
    {
        SKYLIB_ASSERT_SOME(index);

        if (!Is_Empty()) {
            Index_t idx = 0;
            for (Node_t* node = &head; node; node = node->next, idx += 1) {
                if (idx == index()) {
                    return &node->value;
                }
            }
            return none<Type_t*>();
        } else {
            return none<Type_t*>();
        }
    }

}
