/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    template <typename Type_t>
    class Forward_List_t // tList, BSSimpleList
    {
    public:
        class Node_t
        {
        public:
            Type_t  value;  // 0
            Node_t* next;   // ?
        };

    public:
        Node_t head; // 0 (this really should have been a pointer, to determine if the list is empty!)

    public:
        Bool_t          Is_Empty(); // this is questionable when it comes to non-pointer types.

        maybe<Type_t*>  Point(some<Index_t> index);
    };
    STATIC_ASSERT(sizeof(Forward_List_t<void*>) == 0x10);

    template <typename Type_t>
    using List_t = Forward_List_t<Type_t>;

}
